// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IOpenXRExtensionPlugin.h"
#include "Modules/ModuleInterface.h"
#include "UObject/ObjectMacros.h"
//#include "IBlooOpenXRHMDPlugin.generated.h"


DECLARE_DELEGATE_OneParam(FOnVolumeChange, int);
DECLARE_DELEGATE_TwoParams(FOnPowerFullChange, int, bool);
DECLARE_DELEGATE_OneParam(FOnUsbConnectChange, bool);
DECLARE_DELEGATE_OneParam(FOnScreenLock, bool);
DECLARE_DELEGATE_OneParam(FOnVolumeKeyDown, int);
DECLARE_DELEGATE_OneParam(FOnVolumeKeyUp, int);
DECLARE_DELEGATE(FOnPowerKeyPressOneSecond);
DECLARE_DELEGATE_OneParam(FOnFileInfoAvailable, FString);
DECLARE_DELEGATE_OneParam(FOnSeekCompletedCallBack, int);
DECLARE_DELEGATE_OneParam(FOnPlayerStateChangedCallBack, int);


struct FOnBxrPlayerEventListener
{
	FOnSeekCompletedCallBack OnSeekCompletedCallBack;
	FOnPlayerStateChangedCallBack OnPlayerStateChangedCallBack;
};


class BLOOOPENXRHMD_API IBlooOpenXRHMDPlugin : public IOpenXRExtensionPlugin, public IModuleInterface
{
public:

	virtual FString GetDisplayName()
	{
		return IBlooOpenXRHMDPlugin::BlooOpenXRHMDPluginName;
	}

	static FString BlooOpenXRHMDPluginName;

	// ---- Helper Interfaces ----

	static IBlooOpenXRHMDPlugin* GetBlooOpenXRHMDInstance();

	// ---- Callbacks ----

	/**
	 * 音量有变化后，返回当前音量
	 */
	virtual void SetOnVolumeChange(FOnVolumeChange OnVolumeChange) = 0;

	/**
	 * 电量变化后，返回当前电量（0-100）
	 */
	virtual void SetOnPowerFullChange(FOnPowerFullChange OnPowerFullChange) = 0;

	/**
	 * usb连接
	 */
	virtual void SetOnUsbConnectChange(FOnUsbConnectChange OnUsbConnectChange) = 0;

	/**
	 * 锁屏
	 */
	virtual void SetOnScreenLock(FOnScreenLock OnScreenLock) = 0;

	/**
	 * 头显音量键减
	 * @param status 1- up 抬起 ; 0 -down 按下
	 */
	virtual void SetOnVolumeKeyDown(FOnVolumeKeyDown OnVolumeKeyDown) = 0;

	/**
	* 头显音量键加
	* @param status 1- up 抬起 ; 0 -down 按下
	*/
	virtual void SetOnVolumeKeyUp(FOnVolumeKeyUp OnVolumeKeyUp) = 0;

	/**
	 * 电源键长按
	 */
	virtual void SetOnPowerKeyPressOneSecond(FOnPowerKeyPressOneSecond OnPowerKeyPressOneSecond) = 0;

	/**
	 * 文件分类详情
	 */
	virtual void SetOnFileInfoAvailable(FOnFileInfoAvailable OnFileInfoAvailable) = 0;


	// ---- Haptic ----

	/**
	 * Set data source
	 * 配置振动播放器实例的数据源、强度、频率等
	 *
	 * 注意，双手不能取代左右手，系统维护3个震动播放器，三个播放器相互独立，
	 * 播放双手的震动播放器之前，系统将会强制停止此前设置的所有的单独的左、右手的震动。
	 *
	 * @param he 将要播放的he字符串。推荐he2.0格式，兼容he1.0。
	 * @param amplitude 强度，范围[0, 255]
	 * @param freq 变频，改变原始信号中的基频（原来的基频增加此值），一般传0
	 * @param loopCount 再循环次数，0表示播放完成后不再循环。
	 * @param interval 循环间隔，单位毫秒
	 * @param handShank 左手1;右手2;双手3;
	 */
	virtual void SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank) = 0;

	/**
	 * Set data source
	 * 配置振动播放器实例的数据源、强度、频率等
	 *
	 * 注意，双手不能取代左右手，系统维护3个震动播放器，三个播放器相互独立，
	 * 播放双手的震动播放器之前，系统将会强制停止此前设置的所有的单独的左、右手的震动。
	 *
	 * @param amplitude 强度，范围[0, 255]
	 * @param freq 变频，改变原始信号中的基频（原来的基频增加此值），一般传0
	 * @param duration 震动时长，范围[48, 5000]，单位毫秒
	 * @param loopCount 再循环次数，0表示播放完成后不再循环。
	 * @param interval 循环间隔，单位毫秒
	 * @param handShank 左手1;右手2;双手3;
	 */
	virtual void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank) = 0;

    /**
     * Prepare haptic
     * 振动播放器播放前进行数据的预处理，在 setDataSource()之后 start()之前调用
     * @param handShank 左手1;右手2;双手3;
     */
    virtual void PrepareHaptic(int handShank) = 0;

    /**
     * Start haptic
     * 振动播放器开始播放
     * @param handShank 左手1;右手2;双手3;
     */
	virtual void StartHaptic(int handShank) = 0;

    /**
     * Pause haptic
     * 暂停播放setDataSource接口指定的he文件，可以通过start接口从暂停的位置恢复播放。
     * @param handShank 左手1;右手2;双手3;
     */
	virtual void PauseHaptic(int handShank) = 0;

    /**
     * Stop haptic
     *停止播放。如果需要再次播放需要重新setDataSource()。
     * @param handShank 左手1;右手2;双手3;
     */
	virtual void StopHaptic(int handShank) = 0;

    /**
     * Update haptic
     * 用来调整信号的的强度缩放幅度和间隔。
     * @param intensity 强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255
     * @param freq 表示变频，在原有信号基频的基础上加此值，一般传0
     * @param interval 表示循环播放中每次播放结束到下次开始的时间，取值范围大于0
     * @param handShank 左手1;右手2;双手3;
     */
	virtual void UpdateHaptic(int intensity, int freq, int interval, int handShank) = 0;

    /**
     * Seek to
     * 搜索到he文件的指定位置，如果当前正处于播放状态，则从该位置继续播放。
     * @param millSeconds 偏离he起始位置的毫秒数
     * @param handShank 左手1;右手2;双手3;
     */
	virtual void SeekTo(int millSeconds, int handShank) = 0;

    /**
     * Is playing
     * 判断当前是否正在播放状态。
     * @param handShank 左手1;右手2;双手3;
     * @return  true 表示正在播放；false 表示振动播放器未处于播放状态
     */
	virtual bool IsPlaying(int handShank) = 0;

    /**
        * Get duration
        * 返回setDataSource接口指定的he文件的总时长，单位是毫秒。需要在prepare()后调用，才能获取有效的值。
        * @param handShank 左手1;右手2;双手3;
        * @return 已经指定的he文件的总时长，单位是毫秒。
        */
	virtual int32 GetDuration(int handShank) = 0;

    /**
        * Add bxr player event listener
        * 注册振动播放器的状态监听器。
        * listener：android.app.OnBxrPlayerEventListener 对象，需要实现以下两个方法
        * onSeekCompletedCallBack:调用SeekTo方法，完成后会回调；（注意，当前此回调有Bug，在每次循环播放完成一次后都会回调，说明其sdk内部也是使用的seekTo方法实现的循环播放，需要等待RichTap的解决）
        * onPlayerStateChangedCallBack：Player的所有状态变化都会回调
        * BxrManager.RT_IDLE = 0;
        * BxrManager.RT_END = 1;
        * BxrManager.RT_ERRORR = 2;
        * BxrManager.RT_INITIALIZED = 3;
        * BxrManager.RT_PREPARING = 4;
        * BxrManager.RT_PREPARED = 5;
        * BxrManager.RT_STARTED = 6;
        * BxrManager.RT_PAUSED = 7;
        * BxrManager.RT_STOPPED = 8;
        * BxrManager.RT_COMPLETED = 9;
        *
        * @param listener  android.app.OnBxrPlayerEventListener 对象
        * @param handShank 左手1;右手2;双手3;
        */
	virtual void AddBxrPlayerEventListener(FOnBxrPlayerEventListener listener, int handShank) = 0;

    /**
     * Remove bxr player event listener
     * 移除振动播放器的状态监听器。
     * @param handShank 左手1;右手2;双手3;
     */
	virtual void RemoveBxrPlayerEventListener(int handShank) = 0;
};