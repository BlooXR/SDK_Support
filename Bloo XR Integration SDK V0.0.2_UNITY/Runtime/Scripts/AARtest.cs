using System;
using Newtonsoft.Json;
using UnityEngine;

namespace SDK_API
{
    [System.Serializable]
  

    public class AARtest : MonoSingleton<AARtest>
    {
        private AndroidJavaClass javaClass;
        private AndroidJavaObject javaObject;
        private DeviceInfoJavaProxy callback;
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
#endif
        }

       
        /// <summary>
        /// ����he��ʽ���ִ���ʾ����Ч��
        /// </summary>
        /// <param name="heStr">��ʾһ��he��ʽ���ִ�</param>
        /// <param name="loop">��ʾ��ѭ��������ȡֵ��Χ�Ǵ��ڵ���-1��-1��ʾ������ѭ����0��ʾ����1��</param>
        /// <param name="interval">��ʾѭ�����������β���֮���ʱ����</param>
        /// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
        /// <param name="freq">��ʾ��Ƶ����ԭ���źŻ�Ƶ�Ļ����ϼӴ�ֵ��һ�㴫0</param>
        /// <param name="handShank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
        /// <param name="enforceStop">TODO</param>
        public void PlayHeStringHaptic(string heStr, int loop, int interval,
            int intensity, int freq, int handShank, bool enforceStop)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "playHeStringHaptic",
                heStr, loop, interval, intensity, freq, handShank, enforceStop);
        }

        /// <summary>
        /// ����Ԥ�õ���Ч��
        /// </summary>
        /// <param name="prebakedId">��Ч����ţ����Դ� PrebakedId �л�ȡ</param>
        /// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
        /// <param name="handshank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
        public void PlayJoystickExtPrebaked(int prebakedId, int intensity, int handshank)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "playJoystickExtPrebaked",
                prebakedId, intensity, handshank);
        }

        /// <summary>
        /// ����һ��ָ��ǿ�ȡ�Ƶ�ʡ�ʱ������
        /// </summary>
        /// <param name="amplitude">ǿ�ȣ�ȡֵ��Χ[0, 255]</param>
        /// <param name="freq">Ƶ�ʣ�ȡֵ��Χ[1,100]</param>
        /// <param name="duration">ʱ��������������ȡֵ[48, 5000]</param>
        /// <param name="handshank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
        public void PlayCustomHaptic(int amplitude, int freq, int duration, int handshank)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "stopHaptic",
                amplitude);
            Debug.Log("PlayCustomHaptic have done");
        }

        /// <summary>
        /// Send loop parameter
        /// </summary>
        /// <param name="intensity">ǿ�����ű�������Χ[0, 255]��255��ʾ�ź��б궨ǿ�ȵ�100%��һ�㴫255</param>
        /// <param name="interval">��ʾѭ��������ÿ�β��Ž������´ο�ʼ��ʱ�䣬ȡֵ��Χ����0</param>
        /// <param name="freq">��ʾ��Ƶ����ԭ���źŻ�Ƶ�Ļ����ϼӴ�ֵ��һ�㴫0</param>
        /// <param name="handshank">��ʾҪ�������ĸ��ֱ� 0 �� 1 ����  2 ����  3 ˫��</param>
        public void SendLoopParameter(int intensity, int interval, int freq, int handshank)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "sendLoopParameter",
                intensity, interval, freq, handshank);
        }

     
    }

    public class DeviceInfoJavaProxy : AndroidJavaProxy
    {
        public DeviceInfoJavaProxy() : base("com.blooxr.deviceinfo.callback.DeviceInfoCallback")
        {
        }   
    }
}