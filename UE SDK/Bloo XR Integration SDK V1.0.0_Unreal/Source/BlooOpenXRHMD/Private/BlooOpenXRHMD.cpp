// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlooOpenXRHMD.h"
#include "OpenXRCore.h"

#include "DefaultSpectatorScreenController.h"
#include "Modules/ModuleManager.h"
#include "BlooOpenXRHMD_JNI.h"
#include "Runtime/HeadMountedDisplay/Public/IHeadMountedDisplayModule.h"
#include "IOpenXRHMDPlugin.h"
#include "IOpenXRExtensionPlugin.h"
#include "IBlooOpenXRHMDPlugin.h"
#include <JsonUtilities/Public/JsonObjectConverter.h>

#if PLATFORM_ANDROID
#include "Android/AndroidPlatformMisc.h"
#include "OpenXRPlatformRHI.h"
#include <dlfcn.h> 
#endif //PLATFORM_ANDROID

DEFINE_LOG_CATEGORY(LogBlooOpenXRPlugin);

FOnVolumeChange				FBlooOpenXRHMD::OnVolumeChange;
FOnPowerFullChange			FBlooOpenXRHMD::OnPowerFullChange;
FOnUsbConnectChange			FBlooOpenXRHMD::OnUsbConnectChange;
FOnScreenLock				FBlooOpenXRHMD::OnScreenLock;
FOnVolumeKeyDown			FBlooOpenXRHMD::OnVolumeKeyDown;
FOnVolumeKeyUp				FBlooOpenXRHMD::OnVolumeKeyUp;
FOnPowerKeyPressOneSecond	FBlooOpenXRHMD::OnPowerKeyPressOneSecond;
FOnFileInfoAvailable		FBlooOpenXRHMD::OnFileInfoAvailable;
FOnBxrPlayerEventListener	FBlooOpenXRHMD::OnBxrPlayerEventListenerLeft;
FOnBxrPlayerEventListener	FBlooOpenXRHMD::OnBxrPlayerEventListenerRight;
FOnBxrPlayerEventListener	FBlooOpenXRHMD::OnBxrPlayerEventListenerBoth;
FString						IBlooOpenXRHMDPlugin::BlooOpenXRHMDPluginName = "Bloo OpenXR HMD";


//// ---- Device ----
//
////���û���ģʽ
//virtual void SetEyeProtection(bool status) = 0;
//
////��ȡ����ģʽ״̬
//virtual bool IsEyeProtection() = 0;
//
////����adb״̬
//virtual void SetAdbState(bool enable) = 0;
//
////adb״̬ 
//virtual bool IsAdbEnabled() = 0;
//
////��������
//virtual void SetVolume(int volume) = 0;
//
////��ȡ����
//virtual int GetVolume() = 0;
//
////��ȡ�������
//virtual int GetMaxVolume() = 0;
//
////��ȡ����
//virtual int GetPower() = 0;
//
////�Ƿ���
//virtual bool IsCharging() = 0;
//
////��ȡϵͳʱ��
//virtual int64 GetSystemTime() = 0;
//
////����ϵͳʱ��
//virtual void SetSystemTime(int64 time) = 0;
//
//
//// ---- Wifi ----
//
////����wifi
//virtual void ConnectWifi(FString ssid, FString password, int type) = 0;
//
////�Ͽ�wifi
//virtual void DisConnectWifi(FString ssid) = 0;
//
////wifi����״̬
//virtual bool IsWifiOpen() = 0;
//
//
//// ---- Bluetooth ----
//
//// �豸�����Ƿ���
//virtual bool IsBluetoothOpen() = 0;
//
//// ��ȡ�豸��������
//virtual FString GetBluetoothName() = 0;
//
//// ��ȡ�豸������ַ
//virtual FString GetBluetoothAddress() = 0;


IOpenXRHMDPlugin* GetHMD()
{
	if (!IHeadMountedDisplayModule::IsAvailable())
	{
		return nullptr;
	}

	return (IOpenXRHMDPlugin*)&IHeadMountedDisplayModule::Get();
}

IBlooOpenXRHMDPlugin* IBlooOpenXRHMDPlugin::GetBlooOpenXRHMDInstance()
{
	/*IHeadMountedDisplayModule* HMD = GetHMD();
	if (HMD == nullptr)
	{
		UE_LOG(LogBlooOpenXRPluginTest, Error, TEXT("Failed to get IHeadMountedDisplayModule.");
		return nullptr;
	}

	return nullptr;*/

	TArray<IOpenXRExtensionPlugin*> ExtModules = IModularFeatures::Get().GetModularFeatureImplementations<IOpenXRExtensionPlugin>(IOpenXRExtensionPlugin::GetModularFeatureName());
	for (IOpenXRExtensionPlugin* Plugin : ExtModules)
	{
		UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("IOpenXRExtensionPlugin Name: %s."), *Plugin->GetDisplayName());
		if (Plugin->GetDisplayName() == IBlooOpenXRHMDPlugin::BlooOpenXRHMDPluginName)
		{
			return (IBlooOpenXRHMDPlugin*)Plugin;
		}
	}

	return nullptr;
}

bool FBlooOpenXRHMD::GetCustomLoader(PFN_xrGetInstanceProcAddr* OutGetProcAddr)
{
#if PLATFORM_ANDROID
	// clear errors
	dlerror();

	LoaderHandle = FPlatformProcess::GetDllHandle(TEXT("libopenxr_loader.so"));
	if (LoaderHandle == nullptr)
	{
		UE_LOG(LogBlooOpenXRPlugin, Error, TEXT("Unable to load libopenxr_loader.so, error %s"), ANSI_TO_TCHAR(dlerror()));
		return false;
	}

	// clear errors
	dlerror();

	PFN_xrGetInstanceProcAddr xrGetInstanceProcAddrPtr = (PFN_xrGetInstanceProcAddr)FPlatformProcess::GetDllExport(LoaderHandle, TEXT("xrGetInstanceProcAddr"));
	if (xrGetInstanceProcAddrPtr == nullptr)
	{
		UE_LOG(LogBlooOpenXRPlugin, Error, TEXT("Unable to load OpenXR xrGetInstanceProcAddr, error %s"), ANSI_TO_TCHAR(dlerror()));
		return false;
	}
	*OutGetProcAddr = xrGetInstanceProcAddrPtr;

	extern struct android_app* GNativeAndroidApp;
	PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
	xrGetInstanceProcAddrPtr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&xrInitializeLoaderKHR);
	if (xrInitializeLoaderKHR == nullptr)
	{
		UE_LOG(LogBlooOpenXRPlugin, Error, TEXT("Unable to load OpenXR xrInitializeLoaderKHR"));
		return false;
	}
	XrLoaderInitInfoAndroidKHR LoaderInitializeInfoAndroid;
	LoaderInitializeInfoAndroid.type = XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR;
	LoaderInitializeInfoAndroid.next = NULL;
	LoaderInitializeInfoAndroid.applicationVM = GNativeAndroidApp->activity->vm;
	LoaderInitializeInfoAndroid.applicationContext = GNativeAndroidApp->activity->clazz;
	XR_ENSURE(xrInitializeLoaderKHR((XrLoaderInitInfoBaseHeaderKHR*)&LoaderInitializeInfoAndroid));

	UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Loaded Bloo OpenXR Loader"));
	return true;
#else //PLATFORM_ANDROID
	return false;
#endif //PLATFORM_ANDROID
}

bool FBlooOpenXRHMD::IsStandaloneStereoOnlyDevice()
{
#if PLATFORM_ANDROID
	// todo
	//return FAndroidMisc::GetDeviceMake() == FString("Oculus");
	return true;
#else
	return false;
#endif
}

bool FBlooOpenXRHMD::GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	return true;
}

bool FBlooOpenXRHMD::GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR GetInteractionProfile"));

	/*UE_LOG(LogQtiOpenXRHMD, Log, TEXT("Qti OpenXR GetInteractionProfile"));
	OutKeyPrefix = "SimpleController";
	xrStringToPath(InInstance, "/interaction_profiles/khr/simple_controller", &OutPath);
	OutHasHaptics = true;*/

	return true;
}

bool FBlooOpenXRHMD::GetSpectatorScreenController(FHeadMountedDisplayBase* InHMDBase, TUniquePtr<FDefaultSpectatorScreenController>& OutSpectatorScreenController)
{
//#if PLATFORM_ANDROID
//	if (isStandaloneDevice)
//	{
//		//disable SpectatorScreen for standalone device
//		OutSpectatorScreenController = nullptr;
//		return true;
//	}
//	else
//	{
//		OutSpectatorScreenController = MakeUnique<FQtiSpectatorScreenController>(InHMDBase);
//		return true;
//	}
//#else // PLATFORM_ANDROID
//
//	OutSpectatorScreenController = nullptr;
//	return true;
//#endif

#if PLATFORM_ANDROID
	OutSpectatorScreenController = nullptr;
	return true;
#else // PLATFORM_ANDROID
	OutSpectatorScreenController = MakeUnique<FDefaultSpectatorScreenController>(InHMDBase);
	return false;
#endif // PLATFORM_ANDROID
}

void FBlooOpenXRHMD::AddActions(XrInstance Instance, TFunction<XrAction(XrActionType InActionType, const FName& InName, const TArray<XrPath>& InSubactionPaths)> AddAction)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR AddActions"));
	return;
}

void FBlooOpenXRHMD::OnEvent(XrSession InSession, const XrEventDataBaseHeader* InHeader)
{
	return;
}

const void* FBlooOpenXRHMD::OnCreateInstance(class IOpenXRHMDPlugin* InPlugin, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnCreateInstance"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnGetSystem(XrInstance InInstance, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnGetSystem"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnCreateSession(XrInstance InInstance, XrSystemId InSystem, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnCreateSession"));
#if PLATFORM_ANDROID
	if (GRHISupportsRHIThread && GIsThreadedRendering && GUseRHIThread_InternalUseOnly)
	{
		SetRHIThreadEnabled(false, false);
	}
#endif // PLATFORM_ANDROID
	return InNext;
}

const void* FBlooOpenXRHMD::OnBeginSession(XrSession InSession, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnBeginSession"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnBeginFrame(XrSession InSession, XrTime DisplayTime, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnBeginFrame"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnBeginProjectionView(XrSession InSession, int32 InLayerIndex, int32 InViewIndex, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnBeginProjectionView"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnBeginDepthInfo(XrSession InSession, int32 InLayerIndex, int32 InViewIndex, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnBeginDepthInfo"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnEndProjectionLayer(XrSession InSession, int32 InLayerIndex, const void* InNext, XrCompositionLayerFlags& OutFlags)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnEndProjectionLayer"));

	// XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT is required right now because the Bloo mobile runtime blends using alpha otherwise,
	// and we don't have proper inverse alpha support in OpenXR yet (once OpenXR supports inverse alpha, or we change the runtime behavior, remove this)
	OutFlags |= XR_COMPOSITION_LAYER_CORRECT_CHROMATIC_ABERRATION_BIT;
	return InNext;
}

const void* FBlooOpenXRHMD::OnEndFrame(XrSession InSession, XrTime DisplayTime, const TArray<XrSwapchainSubImage> InColorImages, const TArray<XrSwapchainSubImage> InDepthImages, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnEndFrame"));
	return InNext;
}

const void* FBlooOpenXRHMD::OnSyncActions(XrSession InSession, const void* InNext)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR OnSyncActions"));
	return InNext;
}

void FBlooOpenXRHMD::PostSyncActions(XrSession InSession)
{
	//UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("Bloo OpenXR PostSyncActions"));
	return;
}

void FBlooOpenXRHMD::SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SetDataSource(he, amplitude, freq, loopCount, interval, handShank);
#endif
}

void FBlooOpenXRHMD::SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SetCustomDataSource(amplitude, freq, duration, loopCount, interval, handShank);
#endif
}

//void FBlooOpenXRHMD::SetDataSource(const FHapticData& data, int amplitude, int freq, int loopCount, int interval, int handShank)
//{
//#if PLATFORM_ANDROID
//	FString Json;
//	if (FJsonObjectConverter::UStructToJsonObjectString(data, Json))
//	{
//		UE_LOG(LogBlooOpenXRPlugin, Log, TEXT("%s"), *Json);
//		SetDataSource(Json, amplitude, freq, loopCount, interval, handShank);
//	}
//	else
//	{
//		UE_LOG(LogBlooOpenXRPlugin, Error, TEXT("Unable to SetDataSource with FHapticData"));
//	}
//#endif
//}

void FBlooOpenXRHMD::PrepareHaptic(int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().PrepareHaptic(handShank);
#endif
}

void FBlooOpenXRHMD::StartHaptic(int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().StartHaptic(handShank);
#endif
}

void FBlooOpenXRHMD::PauseHaptic(int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().PauseHaptic(handShank);
#endif
}

void FBlooOpenXRHMD::StopHaptic(int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().StopHaptic(handShank);
#endif
}

void FBlooOpenXRHMD::UpdateHaptic(int intensity, int freq, int interval, int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().UpdateHaptic(intensity, freq, interval, handShank);
#endif
}

void FBlooOpenXRHMD::SeekTo(int millSeconds, int handShank)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SeekTo(millSeconds, handShank);
#endif
}

bool FBlooOpenXRHMD::IsPlaying(int handShank)
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().IsPlaying(handShank);
#else
	return false;
#endif
}

int32 FBlooOpenXRHMD::GetDuration(int handShank)
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetDuration(handShank);
#else
	return 0;
#endif
}

void FBlooOpenXRHMD::AddBxrPlayerEventListener(FOnBxrPlayerEventListener listener, int handShank)
{
//#if PLATFORM_ANDROID
//	FBlooOpenXRHMDJNI::GetInstance().AddBxrPlayerEventListener(listener, handShank);
//#endif
	if (handShank == 1)
	{
		OnBxrPlayerEventListenerLeft = listener;
	}
	else if (handShank == 2)
	{
		OnBxrPlayerEventListenerRight = listener;
	}
	else if (handShank == 3)
	{
		OnBxrPlayerEventListenerBoth = listener;
	}
}

void FBlooOpenXRHMD::RemoveBxrPlayerEventListener(int handShank)
{
//#if PLATFORM_ANDROID
//	FBlooOpenXRHMDJNI::GetInstance().RemoveBxrPlayerEventListener(handShank);
//#endif
	if (handShank == 1)
	{
		OnBxrPlayerEventListenerLeft.OnPlayerStateChangedCallBack.Unbind();
		OnBxrPlayerEventListenerLeft.OnSeekCompletedCallBack.Unbind();
	}
	else if (handShank == 2)
	{
		OnBxrPlayerEventListenerRight.OnPlayerStateChangedCallBack.Unbind();
		OnBxrPlayerEventListenerRight.OnSeekCompletedCallBack.Unbind();
	}
	else if (handShank == 3)
	{
		OnBxrPlayerEventListenerBoth.OnPlayerStateChangedCallBack.Unbind();
		OnBxrPlayerEventListenerBoth.OnSeekCompletedCallBack.Unbind();
	}
}

//���û���ģʽ
void FBlooOpenXRHMD::SetEyeProtection(bool status)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SetEyeProtection(status);
#endif
}

//��ȡ����ģʽ״̬
bool FBlooOpenXRHMD::IsEyeProtection()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().IsEyeProtection();
#else
	return false;
#endif
}

//����adb״̬
void FBlooOpenXRHMD::SetAdbState(bool enable)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SetAdbState(enable);
#endif
}

//adb״̬ 
bool FBlooOpenXRHMD::IsAdbEnabled()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().IsAdbEnabled();
#else
	return false;
#endif
}

//��������
void FBlooOpenXRHMD::SetVolume(int volume)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SetVolume(volume);
#endif
}

//��ȡ����
int FBlooOpenXRHMD::GetVolume()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetVolume();
#else
	return 0;
#endif
}

//��ȡ�������
int FBlooOpenXRHMD::GetMaxVolume()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetMaxVolume();
#else
	return 0;
#endif
}

//��ȡ����
int FBlooOpenXRHMD::GetPower()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetPower();
#else
	return 0;
#endif
}

//�Ƿ���
bool FBlooOpenXRHMD::IsCharging()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().IsCharging();
#else
	return false;
#endif
}

//��ȡϵͳʱ��
int64 FBlooOpenXRHMD::GetSystemTime()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetSystemTime();
#else
	return 0;
#endif
}

//����ϵͳʱ��
void FBlooOpenXRHMD::SetSystemTime(int64 time)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().SetSystemTime(time);
#endif
}


// ---- Wifi ----

//����wifi
void FBlooOpenXRHMD::ConnectWifi(FString ssid, FString password, int type)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().ConnectWifi(ssid, password, type);
#endif
}

//�Ͽ�wifi
void FBlooOpenXRHMD::DisConnectWifi(FString ssid)
{
#if PLATFORM_ANDROID
	FBlooOpenXRHMDJNI::GetInstance().DisConnectWifi(ssid);
#endif
}

//wifi����״̬
bool FBlooOpenXRHMD::IsWifiOpen()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().IsWifiOpen();
#else
	return false;
#endif
}


// ---- Bluetooth ----

// �豸�����Ƿ���
bool FBlooOpenXRHMD::IsBluetoothOpen()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().IsBluetoothOpen();
#else
	return false;
#endif
}

// ��ȡ�豸��������
FString FBlooOpenXRHMD::GetBluetoothName()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetBluetoothName();
#else
	return FString();
#endif
}

// ��ȡ�豸������ַ
FString FBlooOpenXRHMD::GetBluetoothAddress()
{
#if PLATFORM_ANDROID
	return FBlooOpenXRHMDJNI::GetInstance().GetBluetoothAddress();
#else
	return FString();
#endif
}

IMPLEMENT_MODULE(FBlooOpenXRHMD, BlooOpenXRHMD)