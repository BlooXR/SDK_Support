// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "IBlooOpenXRHMDPlugin.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlooOpenXRPluginJNI, Log, All);

#if PLATFORM_ANDROID
#include "Runtime/Launch/Public/Android/AndroidJNI.h"
#include "Runtime/ApplicationCore/Public/Android/AndroidApplication.h"


class  FBlooOpenXRHMDJNI
{
public:
	FBlooOpenXRHMDJNI();
	~FBlooOpenXRHMDJNI();

	static FBlooOpenXRHMDJNI& GetInstance();

	void Init();

	void PlayHeStringHaptic(const FString& heStr, int loop, int interval, int intensity, int freq, int handShank, bool enforceStop);
	void PlayJoystickExtPrebaked(int prebakedId, int intensity, int handshank);
	void PlayCustomHaptic(int amplitude, int freq, int duration, int handshank);
	void SendLoopParameter(int intensity, int interval, int freq, int handshank);

	void SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank);
	void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank);
	void PrepareHaptic(int handShank);
	void StartHaptic(int handShank);
	void PauseHaptic(int handShank);
	void StopHaptic(int handShank);
	void UpdateHaptic(int intensity, int freq, int interval, int handShank);
	void SeekTo(int millSeconds, int handShank);
	bool IsPlaying(int handShank);
	int32 GetDuration(int handShank);
	void AddBxrPlayerEventListener(FOnBxrPlayerEventListener listener, int handShank);
	void RemoveBxrPlayerEventListener(int handShank);

	void SetEyeProtection(bool status);
	bool IsEyeProtection();
	void SetAdbState(bool enable);
	bool IsAdbEnabled();
	void SetVolume(int volume);
	int GetVolume();
	int GetMaxVolume();
	int GetPower();
	bool IsCharging();
	int64 GetSystemTime();
	void SetSystemTime(int64 time);

	void ConnectWifi(FString ssid, FString password, int type);
	void DisConnectWifi(FString ssid);
	bool IsWifiOpen();

	bool IsBluetoothOpen();
	FString GetBluetoothName();
	FString GetBluetoothAddress();

private:
	bool bInited = false;
};
#endif