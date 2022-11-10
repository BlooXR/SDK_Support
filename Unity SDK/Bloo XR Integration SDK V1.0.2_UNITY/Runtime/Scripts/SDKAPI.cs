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

            InitHaptic();
           
#endif
        }

        private void OnDestroy()
        {
            RemoveBxrPlayerEventListener(3);
            ReleaseHaptic();
        }



        /// <summary>
        /// 获取手柄电量
        /// </summary>
        /// <param name="index">1 左手  2 右手</param>
        /// <returns>高16位表示左手柄信息；低16位表示右手柄信息；通过移位获得的电量分为7档，1-7</returns>
        public int GetControllerBatteryLevel(int index)
        {
            return UnityJavaManager.Instance.CallJava<int>(javaObject, false, "getControllerBatteryLevel", index);
        }

        /// <summary>
        /// 获取连接状态
        /// </summary>
        /// <param name="index">1 左手  2 右手</param>
        /// <returns>高16位表示左手柄信息；低16位表示右手柄信息；</returns>
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
        /// 初始化：使用AAC功能前，请先运行此初始化方法,此接口将在BxrService内创建3个Player
        /// </summary>
        public void InitHaptic()
        {
            Debug.Log("[Vibration] InitHaptic");
            UnityJavaManager.Instance.CallJava(javaObject, false, "initHaptic");
        }

        /// <summary>
        /// 释放此前初始化的3个振动播放器，和Init配对使用
        /// </summary>
        public void ReleaseHaptic()
        {
            Debug.Log("[Vibration] ReleaseHaptic");
            UnityJavaManager.Instance.CallJava(javaObject, false, "releaseHaptic");
        }

        /// <summary>
        /// 配置振动播放器实例的数据源、强度、频率等
        /// 注意，双手不能取代左右手，系统维护3个震动播放器，三个播放器相互独立，
        /// 播放双手的震动播放器之前，系统将会强制停止此前设置的所有的单独的左、右手的震动。
        /// </summary>
        /// <param name="he">将要播放的he字符串。推荐he2.0格式，兼容he1.0。</param>
        /// <param name="amplitude">强度，范围[0, 255]</param>
        /// <param name="freq">变频，改变原始信号中的基频（原来的基频增加此值），一般传0</param>
        /// <param name="loopCount">再循环次数，0表示播放完成后不再循环。</param>
        /// <param name="interval">循环间隔，单位毫秒</param>
        /// <param name="handShank">左手1;右手2;双手3;</param>
        public void SetDataSource(string he, int amplitude, int freq, int loopCount, int interval, int handShank)
        {
            Debug.Log("[Vibration] SetDataSource:" + he + " " + amplitude + " " + freq + " " + loopCount + " " + interval + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "setDataSource", he, amplitude, freq, loopCount, interval, handShank);
        }

        /// <summary>
        /// 配置振动播放器实例的强度、频率、时长、循环次数等
        /// 注意，双手不能取代左右手，系统维护3个震动播放器，三个播放器相互独立，
        /// 播放双手的震动播放器之前，系统将会强制停止此前设置的所有的单独的左、右手的震动。
        /// </summary>
        /// <param name="amplitude">强度，范围[0, 255]</param>
        /// <param name="freq">变频，改变原始信号中的基频（原来的基频增加此值），一般传0</param>
        /// <param name="duration">震动时长，范围[48, 5000]，单位毫秒;</param>
        /// <param name="loopCount">再循环次数，0表示播放完成后不再循环。</param>
        /// <param name="interval">循环间隔，单位毫秒</param>
        /// <param name="handShank">左手1;右手2;双手3;</param>

        public void SetCustomDataSource(int amplitude, int freq, int duration, int loopCount, int interval, int handShank)
        {
            Debug.Log("[Vibration] SetCustomDataSource:" + " " + amplitude + " " + freq + " " + " "+ duration + loopCount + " " + interval + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "setCustomDataSource", amplitude, freq, duration, loopCount, interval, handShank);
        }

        /// <summary>
        /// 振动播放器播放前进行数据的预处理，在 SetDataSource()之后 start()之前调用
        /// </summary>
        /// <param name="index">左手1;右手2;双手3;</param>
        public void PrepareHaptic(int index)
        {
            Debug.Log("[Vibration] PrepareHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "prepareHaptic", index);
        }

        /// <summary>
        /// 振动播放器开始播放
        /// </summary>
        /// <param name="index">左手1;右手2;双手3;</param>
        public void StartHaptic(int index)
        {
            Debug.Log("[Vibration] StartHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "startHaptic", index);
        }

        /// <summary>
        ///  暂停播放SetDataSource接口指定的he文件，可以通过start接口从暂停的位置恢复播放。
        /// </summary>
        /// <param name="index">左手1;右手2;双手3;</param>
        public void PauseHaptic(int index)
        {
            Debug.Log("[Vibration] PauseHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "pauseHaptic", index);
        }

        /// <summary>
        /// 停止播放。如果需要再次播放需要重新SetDataSource()。
        /// </summary>
        /// <param name="index">左手1;右手2;双手3;</param>
        public void StopHaptic(int index)
        {
            Debug.Log("[Vibration] StopHaptic:" + index);
            UnityJavaManager.Instance.CallJava(javaObject, false, "stopHaptic", index);
        }

        /// <summary>
        /// 用来调整信号的的强度缩放幅度和间隔。
        /// </summary>
        /// <param name="intensity">强度缩放比例，范围[0, 255]，255表示信号中标定强度的100%，一般传255</param>
        /// <param name="freq">表示变频，在原有信号基频的基础上加此值，一般传0</param>
        /// <param name="interval">表示循环播放中每次播放结束到下次开始的时间，取值范围大于0</param>
        /// <param name="handShank">左手1;右手2;双手3;</param>
        public void UpdateHaptic(int intensity, int freq, int interval, int handShank)
        {
            Debug.Log("[Vibration] UpdateHaptic:" + intensity + " " + freq + " " + interval + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "updateHaptic", intensity, freq, interval, handShank);
        }

        /// <summary>
        /// 搜索到he文件的指定位置，如果当前正处于播放状态，则从该位置继续播放。
        /// </summary>
        /// <param name="millSeconds">偏离he起始位置的毫秒数</param>
        /// <param name="handShank">左手1;右手2;双手3;</param>
        public void SeekTo(int millSeconds, int handShank)
        {
            Debug.Log("[Vibration] SeekTo:" + millSeconds + " " + handShank);
            UnityJavaManager.Instance.CallJava(javaObject, false, "seekTo", millSeconds, handShank);
        }

        /// <summary>
        /// 判断当前是否正在播放状态。
        /// </summary>
        /// <param name="index">左手1;右手2;双手3;</param>
        /// <returns>IsPlaying</returns>
        public bool IsPlaying(int index)
        {
            bool isPlaying = UnityJavaManager.Instance.CallJava<bool>(javaObject, false, "isPlaying", index);
            Debug.Log("[Vibration] IsPlaying:" + index + " " + isPlaying);
            return isPlaying;
        }

        /// <summary>
        /// 返回SetDataSource接口指定的he文件的总时长，单位是毫秒。需要在prepare()后调用，才能获取有效的值。
        /// </summary>
        /// <param name="index">左手1;右手2;双手3;</param>
        /// <returns>Duration</returns>
        public int GetDuration(int index)
        {
            int duration = UnityJavaManager.Instance.CallJava<int>(javaObject, false, "getDuration", index);
            Debug.Log("[Vibration] GetDuration:" + index + " " + duration);
            return duration;
        }

        /// <summary>
        /// * 注册振动播放器的状态监听器。
        /// </summary>
        /// <param name="listener">监听器</param>
        /// <param name="handShank">左手1;右手2;双手3;</param>
        public void AddBxrPlayerEventListener(HandlerJavaProxy listener, int handShank)
        {
            Debug.Log("[Vibration] AddBxrPlayerEventListener:");
            UnityJavaManager.Instance.CallJava(javaObject, false, "addBxrPlayerEventListener", listener, handShank);
        }

        /// <summary>
        /// 移除振动播放器的状态监听器。
        /// </summary>
        /// <param name="handShank">左手1;右手2;双手3;</param>
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


