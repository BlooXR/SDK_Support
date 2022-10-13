using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace SDK_API {
    public enum HandShankID
    {
        HANDSHANK_LEFT = 1,
        HANDSHANK_RIGHT = 2,
        HANDSHANK_BOTH = 3
    }
    public class SDKAPI : MonoSingleton<SDKAPI>
    {
        private AndroidJavaClass javaClass;
        private AndroidJavaObject javaObject;
        private DeviceInfoJavaProxy callback;
        private HandlerJavaProxy vibrationCallback;
        private const string JavaManagerName = "com.blooxr.deviceinfo.DeviceInfoManager";
        private bool isInit = false;

        protected override void Awake()
        {
            base.Awake();
            Init();
        }

        /// <summary>
        /// ��ʼ��
        /// </summary>
        public void Init()
        {
            if (isInit) return;
            isInit = true;
#if !UNITY_EDITOR
            if (callback == null) callback = new DeviceInfoJavaProxy();
            if (javaClass == null) javaClass = new AndroidJavaClass(JavaManagerName);
            if (javaObject == null)
                javaObject = javaClass.CallStatic<AndroidJavaObject>("init",
                    UnityJavaManager.Instance.MainActivity, false, callback);

            InitHaptic();
           
#endif
        }

        private void OnDestroy()
        {
            RemoveBxrPlayerEventListener(3);
            ReleaseHaptic();
        }



        /// <summary>
        /// ��ȡ�ֱ�����
        /// </summary>
        /// <param name="index">1 ����  2 ����</param>
        /// <returns>��16λ��ʾ���ֱ���Ϣ����16λ��ʾ���ֱ���Ϣ��ͨ����λ��õĵ�����Ϊ7����1-7</returns>
        public int GetControllerBatteryLevel(int index)
        {
            return UnityJavaManager.Instance.CallJava<int>(javaObject, false, "getControllerBatteryLevel", index);
        }

        /// <summary>
        /// ��ȡ����״̬
        /// </summary>
        /// <param name="index">1 ����  2 ����</param>
        /// <returns>��16λ��ʾ���ֱ���Ϣ����16λ��ʾ���ֱ���Ϣ��</returns>
        public int GetControllerConnectStatus(int index)
        {
            if (index == 1)
            {
                int leftStatus = UnityJavaManager.Instance.CallJava<int>(javaObject, false,
                    "getControllerConnectStatus", index);
                leftStatus = (int)((leftStatus & 0xFFFF0000) >> 16);
                return leftStatus;
            }
            else
            {
                int rightStatus = UnityJavaManager.Instance.CallJava<int>(javaObject, false,
                    "getControllerConnectStatus", index);
                rightStatus = rightStatus & 0x0000FFFF;
                return rightStatus;
            }
        }

        /// <summary>
        /// ��ʼ����ʹ��AAC����ǰ���������д˳�ʼ������,�˽ӿڽ���BxrService�ڴ���3��Player
        /// </summary>
        public void InitHaptic()
        {
            Debug.Log("[Vibration] InitHaptic");
            UnityJavaManager.Instance.CallJava(javaObject, false, "initHaptic");
        }

        /// <summary>
        /// �ͷŴ�ǰ��ʼ����3���񶯲���������Init���ʹ��
        /// </summary>
        public void ReleaseHaptic()
        {
            Debug.Log("[Vibration] ReleaseHaptic");
            UnityJavaManager.Instance.CallJava(javaObject, false, "releaseHaptic");
        }

        /// <summary>
        /// �����񶯲�����ʵ��������Դ��ǿ�ȡ�Ƶ�ʵ�
        /// ע�⣬˫�ֲ���ȡ�������֣�ϵͳά��3���𶯲������������������໥������
        /// ����˫�ֵ��𶯲�����֮ǰ��ϵͳ����ǿ��ֹͣ��ǰ���õ����еĵ����������ֵ��𶯡�
        /// </summary>
        /// <param name="he">��Ҫ���ŵ�he�ַ������Ƽ�he2.0��ʽ������he1.0��</param>
        /// <param name="amplitude">ǿ�ȣ���Χ[0, 255]</param>
        /// <param name="freq">��Ƶ���ı�ԭʼ�ź��еĻ�Ƶ��ԭ���Ļ�Ƶ���Ӵ�ֵ����һ�㴫0</param>
        /// <param name="loopCount">��ѭ��������0��ʾ������ɺ���ѭ����</param>
        /// <param name="interval">ѭ���������λ����</param>
        /// <param name="handShank">����1;����2;˫��3;</param>
        public void SetDataSource(string he, int amplitude, int freq, int loopCount, int interval, int handShank)
        {
            Debug.Log("[Vibration] SetDataSource:" + he + " " + amplitude + " " + freq + " " + loopCount + " " + interval + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "setDataSource", he, amplitude, freq, loopCount, interval, handShank);
        }

        /// <summary>
        /// �����񶯲�����ʵ����ǿ�ȡ�Ƶ�ʡ�ʱ����ѭ��������
        /// ע�⣬˫�ֲ���ȡ�������֣�ϵͳά��3���𶯲������������������໥������
        /// ����˫�ֵ��𶯲�����֮ǰ��ϵͳ����ǿ��ֹͣ��ǰ���õ����еĵ����������ֵ��𶯡�
        /// </summary>
        /// <param name="amplitude">ǿ�ȣ���Χ[0, 255]</param>
        /// <param name="freq">��Ƶ���ı�ԭʼ�ź��еĻ�Ƶ��ԭ���Ļ�Ƶ���Ӵ�ֵ����һ�㴫0</param>
        /// <param name="duration">��ʱ������Χ[48, 5000]����λ����;</param>
        /// <param name="loopCount">��ѭ��������0��ʾ������ɺ���ѭ����</param>
        /// <param name="interval">ѭ���������λ����</param>
        /// <param name="handShank">����1;����2;˫��3;</param>

        public void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank)
        {
            Debug.Log("[Vibration] SetCustomDataSource:" + " " + amplitude + " " + freq + " " + " "+ duration + loopCount + " " + interval + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "setCustomDataSource", amplitude, freq, duration, loopCount, interval, handShank);
        }

        /// <summary>
        /// �񶯲���������ǰ�������ݵ�Ԥ������ SetDataSource()֮�� start()֮ǰ����
        /// </summary>
        /// <param name="index">����1;����2;˫��3;</param>
        public void PrepareHaptic(int index)
        {
            Debug.Log("[Vibration] PrepareHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "prepareHaptic", index);
        }

        /// <summary>
        /// �񶯲�������ʼ����
        /// </summary>
        /// <param name="index">����1;����2;˫��3;</param>
        public void StartHaptic(int index)
        {
            Debug.Log("[Vibration] StartHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "startHaptic", index);
        }

        /// <summary>
        ///  ��ͣ����SetDataSource�ӿ�ָ����he�ļ�������ͨ��start�ӿڴ���ͣ��λ�ûָ����š�
        /// </summary>
        /// <param name="index">����1;����2;˫��3;</param>
        public void PauseHaptic(int index)
        {
            Debug.Log("[Vibration] PauseHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "pauseHaptic", index);
        }

        /// <summary>
        /// ֹͣ���š������Ҫ�ٴβ�����Ҫ����SetDataSource()��
        /// </summary>
        /// <param name="index">����1;����2;˫��3;</param>
        public void StopHaptic(int index)
        {
            Debug.Log("[Vibration] StopHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "stopHaptic", index);
        }

        /// <summary>
        /// ���������źŵĵ�ǿ�����ŷ��Ⱥͼ����
        /// </summary>
        /// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
        /// <param name="freq">��ʾ��Ƶ����ԭ���źŻ�Ƶ�Ļ����ϼӴ�ֵ��һ�㴫0</param>
        /// <param name="interval">��ʾѭ��������ÿ�β��Ž������´ο�ʼ��ʱ�䣬ȡֵ��Χ����0</param>
        /// <param name="handShank">����1;����2;˫��3;</param>
        public void UpdateHaptic(int intensity, int freq, int interval, int handShank)
        {
            Debug.Log("[Vibration] UpdateHaptic:" + intensity + " " + freq + " " + interval + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "updateHaptic", intensity, freq, interval, handShank);
        }

        /// <summary>
        /// ������he�ļ���ָ��λ�ã������ǰ�����ڲ���״̬����Ӹ�λ�ü������š�
        /// </summary>
        /// <param name="millSeconds">ƫ��he��ʼλ�õĺ�����</param>
        /// <param name="handShank">����1;����2;˫��3;</param>
        public void SeekTo(int millSeconds, int handShank)
        {
            Debug.Log("[Vibration] SeekTo:" + millSeconds + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "seekTo", millSeconds, handShank);
        }

        /// <summary>
        /// �жϵ�ǰ�Ƿ����ڲ���״̬��
        /// </summary>
        /// <param name="index">����1;����2;˫��3;</param>
        /// <returns>IsPlaying</returns>
        public bool IsPlaying(int index)
        {
            bool isPlaying = UnityJavaManager.Instance.CallJava<bool>(javaObject, false, "isPlaying", index);
            Debug.Log("[Vibration] IsPlaying:" + index + " " + isPlaying);
            return isPlaying;
        }

        /// <summary>
        /// ����SetDataSource�ӿ�ָ����he�ļ�����ʱ������λ�Ǻ��롣��Ҫ��prepare()����ã����ܻ�ȡ��Ч��ֵ��
        /// </summary>
        /// <param name="index">����1;����2;˫��3;</param>
        /// <returns>Duration</returns>
        public int GetDuration(int index)
        {
            int duration = UnityJavaManager.Instance.CallJava<int>(javaObject, false, "getDuration", index);
            Debug.Log("[Vibration] GetDuration:" + index + " " + duration);
            return duration;
        }

        /// <summary>
        /// * ע���񶯲�������״̬��������
        /// </summary>
        /// <param name="listener">������</param>
        /// <param name="handShank">����1;����2;˫��3;</param>
        public void AddBxrPlayerEventListener(HandlerJavaProxy listener, int handShank)
        {
            Debug.Log("[Vibration] AddBxrPlayerEventListener:");
            UnityJavaManager.Instance.CallJava(javaObject, false, "addBxrPlayerEventListener", listener, handShank);
        }

        /// <summary>
        /// �Ƴ��񶯲�������״̬��������
        /// </summary>
        /// <param name="handShank">����1;����2;˫��3;</param>
        public void RemoveBxrPlayerEventListener(int handShank)
        {
            Debug.Log("[Vibration] RemoveBxrPlayerEventListener:");
            UnityJavaManager.Instance.CallJava(javaObject, false, "removeBxrPlayerEventListener", handShank);
        }
    }

    public class DeviceInfoJavaProxy : AndroidJavaProxy
    {
        public DeviceInfoJavaProxy() : base("com.blooxr.deviceinfo.callback.DeviceInfoCallback")
        {
        }

    }

    public class HandlerJavaProxy : AndroidJavaProxy
    {
        public HandlerJavaProxy() : base("android.app.OnBxrPlayerEventListener")
        {
        }

    }
}


