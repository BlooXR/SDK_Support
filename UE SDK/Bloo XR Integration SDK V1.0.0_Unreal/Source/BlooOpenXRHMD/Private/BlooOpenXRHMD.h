// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "IBlooOpenXRHMDPlugin.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlooOpenXRPlugin, Log, All);

// Haptic Struct

//USTRUCT()
//struct FHapticCurveKey
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY()
//		int8 Frequency;
//
//	UPROPERTY()
//		float Intensity;
//
//	UPROPERTY()
//		float Time;
//
//	FHapticCurveKey()
//		: Frequency(60)
//		, Intensity(100.0f)
//		, Time(0.0f)
//	{}
//};
//
//USTRUCT()
//struct FHapticEventParameters
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY()
//		int8 Frequency;
//
//	UPROPERTY()
//		float Intensity;
//
//	UPROPERTY()
//		TArray<FHapticCurveKey> Curve;
//
//	FHapticEventParameters()
//		: Frequency(60)
//		, Intensity(100.0f)
//	{}
//};
//
//
//USTRUCT()
//struct FHapticEvent
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY()
//		int32 Duration;
//
//	UPROPERTY()
//		FHapticEventParameters Parameters;
//
//	UPROPERTY()
//		FString Type;
//
//	UPROPERTY()
//		int RelativeTime;
//
//	FHapticEvent()
//		: Duration(0)
//		, Type(TEXT("continuous"))
//		, RelativeTime(0)
//	{}
//};
//
//USTRUCT()
//struct FHapticMetadata
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY()
//		int32 Version;
//
//	UPROPERTY()
//		FString Created;
//
//	UPROPERTY()
//		FString Description;
//
//	FHapticMetadata()
//		: Version(1)
//		, Created(TEXT("2022-09-28"))
//		, Description(TEXT("continuous"))
//	{}
//};
//
//USTRUCT()
//struct FHapticPattern
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY()
//		TArray<FHapticEvent> Event;
//
//	FHapticPattern()
//	{}
//};
//
//USTRUCT()
//struct FHapticData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY()
//		FHapticMetadata Metadata;
//
//	UPROPERTY()
//		FHapticPattern Pattern;
//
//	FHapticData()
//	{}
//};


class FBlooOpenXRHMD : public IBlooOpenXRHMDPlugin
{
public:
	FBlooOpenXRHMD()
		: LoaderHandle(nullptr)
	{ }

	virtual ~FBlooOpenXRHMD()
	{ }

	virtual void StartupModule() override
	{
		RegisterOpenXRExtensionModularFeature();
	}

	virtual void ShutdownModule() override
	{
		if (LoaderHandle)
		{
			FPlatformProcess::FreeDllHandle(LoaderHandle);
			LoaderHandle = nullptr;
		}
	}

	virtual FString GetDisplayName() override
	{
		return IBlooOpenXRHMDPlugin::BlooOpenXRHMDPluginName;
	}

	virtual bool GetCustomLoader(PFN_xrGetInstanceProcAddr* OutGetProcAddr) override;
	virtual bool IsStandaloneStereoOnlyDevice() override;
	virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;
	virtual bool GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics) override;
	virtual bool GetSpectatorScreenController(FHeadMountedDisplayBase* InHMDBase, TUniquePtr<FDefaultSpectatorScreenController>& OutSpectatorScreenController) override;
	virtual void AddActions(XrInstance Instance, TFunction<XrAction(XrActionType InActionType, const FName& InName, const TArray<XrPath>& InSubactionPaths)> AddAction) override;
	virtual void OnEvent(XrSession InSession, const XrEventDataBaseHeader* InHeader) override;
	virtual const void* OnCreateInstance(class IOpenXRHMDPlugin* InPlugin, const void* InNext) override;
	virtual const void* OnGetSystem(XrInstance InInstance, const void* InNext) override;
	virtual const void* OnCreateSession(XrInstance InInstance, XrSystemId InSystem, const void* InNext) override;
	virtual const void* OnBeginSession(XrSession InSession, const void* InNext) override;
	virtual const void* OnBeginFrame(XrSession InSession, XrTime DisplayTime, const void* InNext) override;
	virtual const void* OnBeginProjectionView(XrSession InSession, int32 InLayerIndex, int32 InViewIndex, const void* InNext) override;
	virtual const void* OnBeginDepthInfo(XrSession InSession, int32 InLayerIndex, int32 InViewIndex, const void* InNext) override;
	virtual const void* OnEndProjectionLayer(XrSession InSession, int32 InLayerIndex, const void* InNext, XrCompositionLayerFlags& OutFlags) override;
	virtual const void* OnEndFrame(XrSession InSession, XrTime DisplayTime, const TArray<XrSwapchainSubImage> InColorImages, const TArray<XrSwapchainSubImage> InDepthImages, const void* InNext) override;
	virtual const void* OnSyncActions(XrSession InSession, const void* InNext) override;
	virtual void PostSyncActions(XrSession InSession) override;

	virtual void SetOnVolumeChange(FOnVolumeChange InOnVolumeChange)
	{
		OnVolumeChange = InOnVolumeChange;
	}

	virtual void SetOnPowerFullChange(FOnPowerFullChange InOnPowerFullChange)
	{
		OnPowerFullChange = InOnPowerFullChange;
	}

	virtual void SetOnUsbConnectChange(FOnUsbConnectChange InOnUsbConnectChange)
	{
		OnUsbConnectChange = InOnUsbConnectChange;
	}

	virtual void SetOnScreenLock(FOnScreenLock InOnScreenLock)
	{
		OnScreenLock = InOnScreenLock;
	}

	virtual void SetOnVolumeKeyDown(FOnVolumeKeyDown InOnVolumeKeyDown)
	{
		OnVolumeKeyDown = InOnVolumeKeyDown;
	}

	virtual void SetOnVolumeKeyUp(FOnVolumeKeyUp InOnVolumeKeyUp) 
	{
		OnVolumeKeyUp = InOnVolumeKeyUp;
	}

	virtual void SetOnPowerKeyPressOneSecond(FOnPowerKeyPressOneSecond InOnPowerKeyPressOneSecond)
	{
		OnPowerKeyPressOneSecond = InOnPowerKeyPressOneSecond;
	}

	virtual void SetOnFileInfoAvailable(FOnFileInfoAvailable InOnFileInfoAvailable)
	{
		OnFileInfoAvailable = InOnFileInfoAvailable;
	}

	// ---- Device ----

	//设置护眼模式
	virtual void SetEyeProtection(bool status);

	//获取护眼模式状态
	virtual bool IsEyeProtection();

	//设置adb状态
	virtual void SetAdbState(bool enable);

	//adb状态 
	virtual bool IsAdbEnabled();

	//设置音量
	virtual void SetVolume(int volume);

	//获取音量
	virtual int GetVolume();

	//获取最大音量
	virtual int GetMaxVolume();

	//获取电量
	virtual int GetPower();

	//是否充电
	virtual bool IsCharging();

	//获取系统时间
	virtual int64 GetSystemTime();

	//设置系统时间
	virtual void SetSystemTime(int64 time);


	// ---- Wifi ----

	//连接wifi
	virtual void ConnectWifi(FString ssid, FString password, int type);

	//断开wifi
	virtual void DisConnectWifi(FString ssid);

	//wifi开关状态
	virtual bool IsWifiOpen();


	// ---- Bluetooth ----

	// 设备蓝牙是否开启
	virtual bool IsBluetoothOpen();

	// 获取设备蓝牙名字
	virtual FString GetBluetoothName();

	// 获取设备蓝牙地址
	virtual FString GetBluetoothAddress();


//	/// <summary>
///// 播放he格式的字串表示的振动效果
///// </summary>
///// <param name="heStr">表示一个he格式的字串</param>
///// <param name="loop">表示再循环次数，取值范围是大于等于-1，-1表示无限再循环，0表示播放1次</param>
///// <param name="interval">表示循环播放中两次播放之间的时间间隔</param>
///// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
///// <param name="freq">表示变频，在原有信号基频的基础上加此值，一般传0</param>
///// <param name="handShank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
///// <param name="enforceStop">TODO</param>
//	virtual void PlayHeStringHaptic(FString heStr, int loop, int interval, int intensity, int freq, int handShank, bool enforceStop);
//
//	/// <summary>
//	/// 播放预置的震动效果
//	/// </summary>
//	/// <param name="prebakedId">震动效果编号，可以从 PrebakedId 中获取</param>
//	/// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
//	/// <param name="handshank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
//	virtual void PlayJoystickExtPrebaked(int prebakedId, int intensity, int handshank);
//
//	/// <summary>
//	/// 播放一个指定强度、频率、时长的振动
//	/// </summary>
//	/// <param name="amplitude">强度，取值范围[0, 255]</param>
//	/// <param name="freq">频率，取值范围[1,100]</param>
//	/// <param name="duration">时长（毫秒数），取值[48, 5000]</param>
//	/// <param name="handshank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
//	virtual void PlayCustomHaptic(int amplitude, int freq, int duration, int handshank);
//
//	/// <summary>
//	/// Send loop parameter
//	/// </summary>
//	/// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
//	/// <param name="interval">表示循环播放中每次播放结束到下次开始的时间，取值范围大于0</param>
//	/// <param name="freq">表示变频，在原有信号基频的基础上加此值，一般传0</param>
//	/// <param name="handshank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
//	virtual void SendLoopParameter(int intensity, int interval, int freq, int handshank);


	virtual void SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank);
	//virtual void SetDataSource(const FHapticData& data, int amplitude, int freq, int loopCount, int interval, int handShank);
	virtual void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank);
	virtual void PrepareHaptic(int handShank);
	virtual void StartHaptic(int handShank);
	virtual void PauseHaptic(int handShank);
	virtual void StopHaptic(int handShank);
	virtual void UpdateHaptic(int intensity, int freq, int interval, int handShank);
	virtual void SeekTo(int millSeconds, int handShank);
	virtual bool IsPlaying(int handShank);
	virtual int32 GetDuration(int handShank);
	virtual void AddBxrPlayerEventListener(FOnBxrPlayerEventListener listener, int handShank);
	virtual void RemoveBxrPlayerEventListener(int handShank);

public:

	void* LoaderHandle;
	static FOnVolumeChange OnVolumeChange;
	static FOnPowerFullChange OnPowerFullChange;
	static FOnUsbConnectChange OnUsbConnectChange;
	static FOnScreenLock OnScreenLock;
	static FOnVolumeKeyDown OnVolumeKeyDown;
	static FOnVolumeKeyUp OnVolumeKeyUp;
	static FOnPowerKeyPressOneSecond OnPowerKeyPressOneSecond;
	static FOnFileInfoAvailable OnFileInfoAvailable;

	static FOnBxrPlayerEventListener OnBxrPlayerEventListenerLeft;
	static FOnBxrPlayerEventListener OnBxrPlayerEventListenerRight;
	static FOnBxrPlayerEventListener OnBxrPlayerEventListenerBoth;

private:
	friend class FBlooOpenXRHMDJNI;
};