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
        /// 初始化
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
        /// 播放he格式的字串表示的振动效果
        /// </summary>
        /// <param name="heStr">表示一个he格式的字串</param>
        /// <param name="loop">表示再循环次数，取值范围是大于等于-1，-1表示无限再循环，0表示播放1次</param>
        /// <param name="interval">表示循环播放中两次播放之间的时间间隔</param>
        /// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
        /// <param name="freq">表示变频，在原有信号基频的基础上加此值，一般传0</param>
        /// <param name="handShank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
        /// <param name="enforceStop">TODO</param>
        public void PlayHeStringHaptic(string heStr, int loop, int interval,
            int intensity, int freq, int handShank, bool enforceStop)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "playHeStringHaptic",
                heStr, loop, interval, intensity, freq, handShank, enforceStop);
        }

        /// <summary>
        /// 播放预置的震动效果
        /// </summary>
        /// <param name="prebakedId">震动效果编号，可以从 PrebakedId 中获取</param>
        /// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
        /// <param name="handshank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
        public void PlayJoystickExtPrebaked(int prebakedId, int intensity, int handshank)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "playJoystickExtPrebaked",
                prebakedId, intensity, handshank);
        }

        /// <summary>
        /// 播放一个指定强度、频率、时长的振动
        /// </summary>
        /// <param name="amplitude">强度，取值范围[0, 255]</param>
        /// <param name="freq">频率，取值范围[1,100]</param>
        /// <param name="duration">时长（毫秒数），取值[48, 5000]</param>
        /// <param name="handshank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
        public void PlayCustomHaptic(int amplitude, int freq, int duration, int handshank)
        {
            UnityJavaManager.Instance.CallJava(javaObject, false, "stopHaptic",
                amplitude);
            Debug.Log("PlayCustomHaptic have done");
        }

        /// <summary>
        /// Send loop parameter
        /// </summary>
        /// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
        /// <param name="interval">表示循环播放中每次播放结束到下次开始的时间，取值范围大于0</param>
        /// <param name="freq">表示变频，在原有信号基频的基础上加此值，一般传0</param>
        /// <param name="handshank">表示要运行在哪个手柄 0 无 1 左手  2 右手  3 双手</param>
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