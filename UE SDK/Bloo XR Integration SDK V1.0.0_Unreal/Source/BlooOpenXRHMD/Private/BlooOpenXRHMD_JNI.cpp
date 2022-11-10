// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlooOpenXRHMD_JNI.h"
//#include "OpenXRCore.h"
//#include "OpenXRPlatformRHI.h"
#include "Modules/ModuleManager.h"
#include "BlooOpenXRHMD.h"


DEFINE_LOG_CATEGORY(LogBlooOpenXRPluginJNI);

#if PLATFORM_ANDROID
#include "Android/AndroidPlatformMisc.h"
#include <dlfcn.h> 

FBlooOpenXRHMDJNI& FBlooOpenXRHMDJNI::GetInstance()
{
	static FBlooOpenXRHMDJNI* BlooOpenXRHMDJNI = nullptr;
	if (BlooOpenXRHMDJNI == nullptr)
	{
		BlooOpenXRHMDJNI = new FBlooOpenXRHMDJNI();
	}

	return *BlooOpenXRHMDJNI;
}

FBlooOpenXRHMDJNI::FBlooOpenXRHMDJNI() 
{
	Init();
}

FBlooOpenXRHMDJNI::~FBlooOpenXRHMDJNI()
{

}

void FBlooOpenXRHMDJNI::Init()
{
	if (bInited) 
		return;
	bInited = true;

	//if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	//{
	//	//bool bIsOptional = false;
	//	//static jmethodID MethonId_Test = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "TestFunc", "()V", bIsOptional);
	//	//FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, MethonId_Test);
	//}
}

/*
Table 3-2 Java VM Type Signatures
Type Signature           Java Type
Z                        boolean
B                        byte
C                        char
S                        short
I                        int
J                        long
F                        float
D                        double
L                        fully-qualified-class; fully - qualified - class
[type                    type[]
(arg - types) ret-type   method type

e.g.
long f (int n, String s, int[] arr);  --->  (ILjava/lang/String;[I)J 

refs: https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/types.html
*/

void FBlooOpenXRHMDJNI::PlayHeStringHaptic(const FString& heStr, int loop, int interval, int intensity, int freq, int handShank, bool enforceStop)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		//bool bIsOptional = false;
		auto JavaStr = FJavaHelper::ToJavaString(Env, heStr);

		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "playHeStringHaptic", "(Ljava/lang/String;IIIIIZ)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, *JavaStr, loop, interval, intensity, freq, handShank, enforceStop);
	}
}

void FBlooOpenXRHMDJNI::PlayJoystickExtPrebaked(int prebakedId, int intensity, int handshank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "playJoystickExtPrebaked", "(III)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, prebakedId, intensity, handshank);
	}
}

void FBlooOpenXRHMDJNI::PlayCustomHaptic(int amplitude, int freq, int duration, int handshank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "playCustomHaptic", "(IIII)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, amplitude, freq, duration, handshank);
	}
}

void FBlooOpenXRHMDJNI::SendLoopParameter(int intensity, int interval, int freq, int handshank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "sendLoopParameter", "(IIII)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, intensity, interval, freq, handshank);
	}
}

void FBlooOpenXRHMDJNI::SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "setDataSource", "(Ljava/lang/String;IIIII)V", false);

		auto JavaStr = FJavaHelper::ToJavaString(Env, he);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, *JavaStr, amplitude, freq, loopCount, interval, handShank);
	}
}

void FBlooOpenXRHMDJNI::SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "setCustomDataSource", "(IIIIII)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, amplitude, freq, duration, loopCount, interval, handShank);
	}
}

void FBlooOpenXRHMDJNI::PrepareHaptic(int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "prepareHaptic", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}
}

void FBlooOpenXRHMDJNI::StartHaptic(int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "startHaptic", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}
}

void FBlooOpenXRHMDJNI::PauseHaptic(int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "pauseHaptic", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}
}

void FBlooOpenXRHMDJNI::StopHaptic(int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "stopHaptic", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}
}

void FBlooOpenXRHMDJNI::UpdateHaptic(int intensity, int freq, int interval, int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "updateHaptic", "(IIII)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, intensity, freq, interval, handShank);
	}
}

void FBlooOpenXRHMDJNI::SeekTo(int millSeconds, int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "startHaptic", "(II)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, millSeconds, handShank);
	}
}

bool FBlooOpenXRHMDJNI::IsPlaying(int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "isPlaying", "(I)Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}

	return false;
}

int32 FBlooOpenXRHMDJNI::GetDuration(int handShank)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getDuration", "(I)I", false);
		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}

	return 0;
}

void FBlooOpenXRHMDJNI::AddBxrPlayerEventListener(FOnBxrPlayerEventListener listener, int handShank)
{
	/*if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "startHaptic", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}*/
}

void FBlooOpenXRHMDJNI::RemoveBxrPlayerEventListener(int handShank)
{
	/*if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "startHaptic", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, handShank);
	}*/
}

//设置护眼模式
void FBlooOpenXRHMDJNI::SetEyeProtection(bool status)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "setEyeProtection", "(Z)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, status);
	}
}

//获取护眼模式状态
bool FBlooOpenXRHMDJNI::IsEyeProtection()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "isEyeProtection", "()Z", false);

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return false;
}

//设置adb状态
void FBlooOpenXRHMDJNI::SetAdbState(bool enable)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "setAdbState", "(Z)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, enable);
	}
}

//adb状态 
bool FBlooOpenXRHMDJNI::IsAdbEnabled()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "isAdbEnabled", "()Z", false);

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return false;
}

//设置音量
void FBlooOpenXRHMDJNI::SetVolume(int volume)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "setVolume", "(I)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, volume);
	}
}

//获取音量
int FBlooOpenXRHMDJNI::GetVolume()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getVolume", "()I", false);

		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return 0;
}

//获取最大音量
int FBlooOpenXRHMDJNI::GetMaxVolume()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getMaxVolume", "()I", false);

		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return 0;
}

//获取电量
int FBlooOpenXRHMDJNI::GetPower()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getPower", "()I", false);

		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return 0;
}

//是否充电
bool FBlooOpenXRHMDJNI::IsCharging()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "isCharging", "()Z", false);

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return false;
}

//获取系统时间
int64 FBlooOpenXRHMDJNI::GetSystemTime()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getSystemTime", "()J", false);

		return FJavaWrapper::CallLongMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return 0;
}

//设置系统时间
void FBlooOpenXRHMDJNI::SetSystemTime(int64 time)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "setSystemTime", "(J)V", false);

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, time);
	}
}


// ---- Wifi ----

//连接wifi
void FBlooOpenXRHMDJNI::ConnectWifi(FString ssid, FString password, int type)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "connectWifi", "(Ljava/lang/String;Ljava/lang/String;I)V", false);

		auto ssidJavaStr = FJavaHelper::ToJavaString(Env, ssid);
		auto passwordJavaStr = FJavaHelper::ToJavaString(Env, password);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, *ssidJavaStr, *passwordJavaStr, type);
	}
}

//断开wifi
void FBlooOpenXRHMDJNI::DisConnectWifi(FString ssid)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "disConnectWifi", "(Ljava/lang/String;I)V", false);

		auto JavaStr = FJavaHelper::ToJavaString(Env, ssid);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId, *JavaStr);
	}
}

//wifi开关状态
bool FBlooOpenXRHMDJNI::IsWifiOpen()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "isWifiOpen", "()Z", false);

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return false;
}


// ---- Bluetooth ----

// 设备蓝牙是否开启
bool FBlooOpenXRHMDJNI::IsBluetoothOpen()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "isBluetoothOpen", "()Z", false);

		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
	}

	return false;
}

// 获取设备蓝牙名字
FString FBlooOpenXRHMDJNI::GetBluetoothName()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getBluetoothName", "()Ljava/lang/String;", false);

		jstring JavaStr = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
		const auto Str = FJavaHelper::FStringFromLocalRef(Env, JavaStr);
		return Str;
	}

	return {};
}

// 获取设备蓝牙地址
FString FBlooOpenXRHMDJNI::GetBluetoothAddress()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID S_MethonId = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getBluetoothAddress", "()Ljava/lang/String;", false);

		jstring JavaStr = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, S_MethonId);
		const auto Str = FJavaHelper::FStringFromLocalRef(Env, JavaStr);
		return Str;
	}

	return {};
}


// ---------- JNI ----------

extern "C" void Java_com_epicgames_ue4_GameActivity_nativePlayHeStringHaptic(JNIEnv * Env, jobject LocalThiz, jint value)
{
	//JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativePlayHeStringHaptic"));
	//int32 CPPValue = value;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(CPPValue));
	
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeTest(JNIEnv * Env, jobject LocalThiz, jstring value)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeTest"));
	jboolean isCopy;
	const char* apkPath = Env->GetStringUTFChars((jstring)value, &isCopy);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(apkPath));
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnVolumeChange(JNIEnv * Env, jobject LocalThiz, jint value)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnVolumeChange"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(value));
	//if (FBlooOpenXRHMD::OnVolumeChange.IsBound())
	{
		FBlooOpenXRHMD::OnVolumeChange.ExecuteIfBound(value);
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnPowerFullChange(JNIEnv * Env, jobject LocalThiz, jint level, jboolean isCharging)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnPowerFullChange"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(level));
	//if (FBlooOpenXRHMD::OnPowerFullChange.IsBound())
	{
		FBlooOpenXRHMD::OnPowerFullChange.ExecuteIfBound(level, isCharging);
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnUsbConnectChange(JNIEnv * Env, jobject LocalThiz, jboolean connect)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnUsbConnectChange"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(connect));
	//if (FBlooOpenXRHMD::OnUsbConnectChange.IsBound())
	{
		FBlooOpenXRHMD::OnUsbConnectChange.ExecuteIfBound(connect);
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnScreenLock(JNIEnv * Env, jobject LocalThiz, jboolean isLock)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnScreenLock"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(isLock));

	//if (FBlooOpenXRHMD::OnScreenLock.IsBound())
	{
		FBlooOpenXRHMD::OnScreenLock.ExecuteIfBound(isLock);
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnVolumeKeyDown(JNIEnv * Env, jobject LocalThiz, jint status)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnVolumeKeyDown"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(status));

	//if (FBlooOpenXRHMD::OnVolumeKeyDown.IsBound())
	{
		FBlooOpenXRHMD::OnVolumeKeyDown.ExecuteIfBound(status);
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnVolumeKeyUp(JNIEnv * Env, jobject LocalThiz, jint status)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnVolumeKeyUp"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(status));
	//if (FBlooOpenXRHMD::OnVolumeKeyUp.IsBound())
	{
		FBlooOpenXRHMD::OnVolumeKeyUp.ExecuteIfBound(status);
	}
}


extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnPowerKeyPressOneSecond(JNIEnv * Env, jobject LocalThiz)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnPowerKeyPressOneSecond"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnPowerKeyPressOneSecond"));
	//if (FBlooOpenXRHMD::OnPowerKeyPressOneSecond.IsBound())
	{
		FBlooOpenXRHMD::OnPowerKeyPressOneSecond.ExecuteIfBound();
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnFileInfoAvailable(JNIEnv * Env, jobject LocalThiz, jstring memoryInfo)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnFileInfoAvailable"));
	jboolean isCopy;
	const char* CharStr = Env->GetStringUTFChars((jstring)memoryInfo, &isCopy);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(CharStr));
	//if (FBlooOpenXRHMD::OnFileInfoAvailable.IsBound())
	{
		FBlooOpenXRHMD::OnFileInfoAvailable.ExecuteIfBound(FString(CharStr));
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativePlayerEventListener(JNIEnv * Env, jobject LocalThiz, jint handShank, jint eventIndex, jint value)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativePlayerEventListener"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(value));

	auto Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerLeft.OnPlayerStateChangedCallBack;
	if (handShank == 1)
	{
		if (eventIndex == 1)
		{
			Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerLeft.OnSeekCompletedCallBack;
		}
		else
		{
			Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerLeft.OnPlayerStateChangedCallBack;
		}
	}
	else if (handShank == 2)
	{
		if (eventIndex == 1)
		{
			Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerRight.OnSeekCompletedCallBack;
		}
		else
		{
			Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerRight.OnPlayerStateChangedCallBack;
		}
	}
	else if (handShank == 3)
	{
		if (eventIndex == 1)
		{
			Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerBoth.OnSeekCompletedCallBack;
		}
		else
		{
			Event = FBlooOpenXRHMD::OnBxrPlayerEventListenerBoth.OnPlayerStateChangedCallBack;
		}
	}

	//if (Event.IsBound())
	{
		Event.ExecuteIfBound(value);
	}
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnWifiConnectStatus(JNIEnv * Env, jobject LocalThiz, jboolean isConnected)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnWifiConnectStatus"));
	
	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnWifiListChange(JNIEnv * Env, jobject LocalThiz, jstring wifiList)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnWifiListChange"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnWifiConnectSuccess(JNIEnv * Env, jobject LocalThiz, jstring ssid)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnWifiConnectSuccess"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnWifiConnectFailure(JNIEnv * Env, jobject LocalThiz, jstring ssid, jint code)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnWifiConnectFailure"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnNetworkAvailable(JNIEnv * Env, jobject LocalThiz, jboolean isAvailablee)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnNetworkAvailable"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothStateChangeOn(JNIEnv * Env, jobject LocalThiz)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothStateChangeOn"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothStateChangeOff(JNIEnv * Env, jobject LocalThiz)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothStateChangeOff"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothScanStarted(JNIEnv * Env, jobject LocalThiz)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothScanStarted"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothScanStop(JNIEnv * Env, jobject LocalThiz)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothScanStop"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothDeviceFound(JNIEnv * Env, jobject LocalThiz, jstring data)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothDeviceFound"));

	// todo
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothConnectionChanged(JNIEnv * Env, jobject LocalThiz, jstring data)
{
	FPlatformMisc::LowLevelOutputDebugString(TEXT("Java_com_epicgames_ue4_GameActivity_nativeOnBlueToothConnectionChanged"));

	// todo
}

#endif //PLATFORM_ANDROID