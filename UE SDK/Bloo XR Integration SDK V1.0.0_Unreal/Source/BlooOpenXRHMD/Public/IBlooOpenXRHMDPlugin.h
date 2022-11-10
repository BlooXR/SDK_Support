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
	 * �����б仯�󣬷��ص�ǰ����
	 */
	virtual void SetOnVolumeChange(FOnVolumeChange OnVolumeChange) = 0;

	/**
	 * �����仯�󣬷��ص�ǰ������0-100��
	 */
	virtual void SetOnPowerFullChange(FOnPowerFullChange OnPowerFullChange) = 0;

	/**
	 * usb����
	 */
	virtual void SetOnUsbConnectChange(FOnUsbConnectChange OnUsbConnectChange) = 0;

	/**
	 * ����
	 */
	virtual void SetOnScreenLock(FOnScreenLock OnScreenLock) = 0;

	/**
	 * ͷ����������
	 * @param status 1- up ̧�� ; 0 -down ����
	 */
	virtual void SetOnVolumeKeyDown(FOnVolumeKeyDown OnVolumeKeyDown) = 0;

	/**
	* ͷ����������
	* @param status 1- up ̧�� ; 0 -down ����
	*/
	virtual void SetOnVolumeKeyUp(FOnVolumeKeyUp OnVolumeKeyUp) = 0;

	/**
	 * ��Դ������
	 */
	virtual void SetOnPowerKeyPressOneSecond(FOnPowerKeyPressOneSecond OnPowerKeyPressOneSecond) = 0;

	/**
	 * �ļ���������
	 */
	virtual void SetOnFileInfoAvailable(FOnFileInfoAvailable OnFileInfoAvailable) = 0;


	// ---- Haptic ----

	/**
	 * Set data source
	 * �����񶯲�����ʵ��������Դ��ǿ�ȡ�Ƶ�ʵ�
	 *
	 * ע�⣬˫�ֲ���ȡ�������֣�ϵͳά��3���𶯲������������������໥������
	 * ����˫�ֵ��𶯲�����֮ǰ��ϵͳ����ǿ��ֹͣ��ǰ���õ����еĵ����������ֵ��𶯡�
	 *
	 * @param he ��Ҫ���ŵ�he�ַ������Ƽ�he2.0��ʽ������he1.0��
	 * @param amplitude ǿ�ȣ���Χ[0, 255]
	 * @param freq ��Ƶ���ı�ԭʼ�ź��еĻ�Ƶ��ԭ���Ļ�Ƶ���Ӵ�ֵ����һ�㴫0
	 * @param loopCount ��ѭ��������0��ʾ������ɺ���ѭ����
	 * @param interval ѭ���������λ����
	 * @param handShank ����1;����2;˫��3;
	 */
	virtual void SetDataSource(const FString& he, int amplitude, int freq, int loopCount, int interval, int handShank) = 0;

	/**
	 * Set data source
	 * �����񶯲�����ʵ��������Դ��ǿ�ȡ�Ƶ�ʵ�
	 *
	 * ע�⣬˫�ֲ���ȡ�������֣�ϵͳά��3���𶯲������������������໥������
	 * ����˫�ֵ��𶯲�����֮ǰ��ϵͳ����ǿ��ֹͣ��ǰ���õ����еĵ����������ֵ��𶯡�
	 *
	 * @param amplitude ǿ�ȣ���Χ[0, 255]
	 * @param freq ��Ƶ���ı�ԭʼ�ź��еĻ�Ƶ��ԭ���Ļ�Ƶ���Ӵ�ֵ����һ�㴫0
	 * @param duration ��ʱ������Χ[48, 5000]����λ����
	 * @param loopCount ��ѭ��������0��ʾ������ɺ���ѭ����
	 * @param interval ѭ���������λ����
	 * @param handShank ����1;����2;˫��3;
	 */
	virtual void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank) = 0;

    /**
     * Prepare haptic
     * �񶯲���������ǰ�������ݵ�Ԥ������ setDataSource()֮�� start()֮ǰ����
     * @param handShank ����1;����2;˫��3;
     */
    virtual void PrepareHaptic(int handShank) = 0;

    /**
     * Start haptic
     * �񶯲�������ʼ����
     * @param handShank ����1;����2;˫��3;
     */
	virtual void StartHaptic(int handShank) = 0;

    /**
     * Pause haptic
     * ��ͣ����setDataSource�ӿ�ָ����he�ļ�������ͨ��start�ӿڴ���ͣ��λ�ûָ����š�
     * @param handShank ����1;����2;˫��3;
     */
	virtual void PauseHaptic(int handShank) = 0;

    /**
     * Stop haptic
     *ֹͣ���š������Ҫ�ٴβ�����Ҫ����setDataSource()��
     * @param handShank ����1;����2;˫��3;
     */
	virtual void StopHaptic(int handShank) = 0;

    /**
     * Update haptic
     * ���������źŵĵ�ǿ�����ŷ��Ⱥͼ����
     * @param intensity ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255
     * @param freq ��ʾ��Ƶ����ԭ���źŻ�Ƶ�Ļ����ϼӴ�ֵ��һ�㴫0
     * @param interval ��ʾѭ��������ÿ�β��Ž������´ο�ʼ��ʱ�䣬ȡֵ��Χ����0
     * @param handShank ����1;����2;˫��3;
     */
	virtual void UpdateHaptic(int intensity, int freq, int interval, int handShank) = 0;

    /**
     * Seek to
     * ������he�ļ���ָ��λ�ã������ǰ�����ڲ���״̬����Ӹ�λ�ü������š�
     * @param millSeconds ƫ��he��ʼλ�õĺ�����
     * @param handShank ����1;����2;˫��3;
     */
	virtual void SeekTo(int millSeconds, int handShank) = 0;

    /**
     * Is playing
     * �жϵ�ǰ�Ƿ����ڲ���״̬��
     * @param handShank ����1;����2;˫��3;
     * @return  true ��ʾ���ڲ��ţ�false ��ʾ�񶯲�����δ���ڲ���״̬
     */
	virtual bool IsPlaying(int handShank) = 0;

    /**
        * Get duration
        * ����setDataSource�ӿ�ָ����he�ļ�����ʱ������λ�Ǻ��롣��Ҫ��prepare()����ã����ܻ�ȡ��Ч��ֵ��
        * @param handShank ����1;����2;˫��3;
        * @return �Ѿ�ָ����he�ļ�����ʱ������λ�Ǻ��롣
        */
	virtual int32 GetDuration(int handShank) = 0;

    /**
        * Add bxr player event listener
        * ע���񶯲�������״̬��������
        * listener��android.app.OnBxrPlayerEventListener ������Ҫʵ��������������
        * onSeekCompletedCallBack:����SeekTo��������ɺ��ص�����ע�⣬��ǰ�˻ص���Bug����ÿ��ѭ���������һ�κ󶼻�ص���˵����sdk�ڲ�Ҳ��ʹ�õ�seekTo����ʵ�ֵ�ѭ�����ţ���Ҫ�ȴ�RichTap�Ľ����
        * onPlayerStateChangedCallBack��Player������״̬�仯����ص�
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
        * @param listener  android.app.OnBxrPlayerEventListener ����
        * @param handShank ����1;����2;˫��3;
        */
	virtual void AddBxrPlayerEventListener(FOnBxrPlayerEventListener listener, int handShank) = 0;

    /**
     * Remove bxr player event listener
     * �Ƴ��񶯲�������״̬��������
     * @param handShank ����1;����2;˫��3;
     */
	virtual void RemoveBxrPlayerEventListener(int handShank) = 0;
};