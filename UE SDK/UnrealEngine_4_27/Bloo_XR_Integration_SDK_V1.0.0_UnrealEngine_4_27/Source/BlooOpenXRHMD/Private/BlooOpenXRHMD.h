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

	//���û���ģʽ
	virtual void SetEyeProtection(bool status);

	//��ȡ����ģʽ״̬
	virtual bool IsEyeProtection();

	//����adb״̬
	virtual void SetAdbState(bool enable);

	//adb״̬ 
	virtual bool IsAdbEnabled();

	//��������
	virtual void SetVolume(int volume);

	//��ȡ����
	virtual int GetVolume();

	//��ȡ�������
	virtual int GetMaxVolume();

	//��ȡ����
	virtual int GetPower();

	//�Ƿ���
	virtual bool IsCharging();

	//��ȡϵͳʱ��
	virtual int64 GetSystemTime();

	//����ϵͳʱ��
	virtual void SetSystemTime(int64 time);


	// ---- Wifi ----

	//����wifi
	virtual void ConnectWifi(FString ssid, FString password, int type);

	//�Ͽ�wifi
	virtual void DisConnectWifi(FString ssid);

	//wifi����״̬
	virtual bool IsWifiOpen();


	// ---- Bluetooth ----

	// �豸�����Ƿ���
	virtual bool IsBluetoothOpen();

	// ��ȡ�豸��������
	virtual FString GetBluetoothName();

	// ��ȡ�豸������ַ
	virtual FString GetBluetoothAddress();


//	/// <summary>
///// ����he��ʽ���ִ���ʾ����Ч��
///// </summary>
///// <param name="heStr">��ʾһ��he��ʽ���ִ�</param>
///// <param name="loop">��ʾ��ѭ��������ȡֵ��Χ�Ǵ��ڵ���-1��-1��ʾ������ѭ����0��ʾ����1��</param>
///// <param name="interval">��ʾѭ�����������β���֮���ʱ����</param>
///// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
///// <param name="freq">��ʾ��Ƶ����ԭ���źŻ�Ƶ�Ļ����ϼӴ�ֵ��һ�㴫0</param>
///// <param name="handShank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
///// <param name="enforceStop">TODO</param>
//	virtual void PlayHeStringHaptic(FString heStr, int loop, int interval, int intensity, int freq, int handShank, bool enforceStop);
//
//	/// <summary>
//	/// ����Ԥ�õ���Ч��
//	/// </summary>
//	/// <param name="prebakedId">��Ч����ţ����Դ� PrebakedId �л�ȡ</param>
//	/// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
//	/// <param name="handshank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
//	virtual void PlayJoystickExtPrebaked(int prebakedId, int intensity, int handshank);
//
//	/// <summary>
//	/// ����һ��ָ��ǿ�ȡ�Ƶ�ʡ�ʱ������
//	/// </summary>
//	/// <param name="amplitude">ǿ�ȣ�ȡֵ��Χ[0, 255]</param>
//	/// <param name="freq">Ƶ�ʣ�ȡֵ��Χ[1,100]</param>
//	/// <param name="duration">ʱ��������������ȡֵ[48, 5000]</param>
//	/// <param name="handshank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
//	virtual void PlayCustomHaptic(int amplitude, int freq, int duration, int handshank);
//
//	/// <summary>
//	/// Send loop parameter
//	/// </summary>
//	/// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
//	/// <param name="interval">��ʾѭ��������ÿ�β��Ž������´ο�ʼ��ʱ�䣬ȡֵ��Χ����0</param>
//	/// <param name="freq">��ʾ��Ƶ����ԭ���źŻ�Ƶ�Ļ����ϼӴ�ֵ��һ�㴫0</param>
//	/// <param name="handshank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
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