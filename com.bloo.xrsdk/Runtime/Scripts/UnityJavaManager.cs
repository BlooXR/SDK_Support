using UnityEngine;

/// <summary>
/// Unity调用Java接口
/// </summary>
public class UnityJavaManager : MonoSingleton<UnityJavaManager>
{
    private AndroidJavaObject currentActivity;

    /// <summary>
    /// 安卓的Activity
    /// </summary>
    public AndroidJavaObject MainActivity
    {
        get
        {
#if !UNITY_EDITOR
            if (currentActivity == null)
            {
                AndroidJavaClass jc = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
                currentActivity = jc.GetStatic<AndroidJavaObject>("currentActivity");
            }
#endif
            return currentActivity;
        }
    }

    private AndroidJavaObject currentContext;
    public AndroidJavaObject Context
    {
        get
        {
#if !UNITY_EDITOR
            if (currentContext == null)
                currentContext = MainActivity.Call<AndroidJavaObject>("getApplicationContext");
#endif
            return currentContext;
        }
    }

    /// <summary>
    /// 调用Java代码，重载（1/8）
    /// </summary>
    public T CallJava<T>(AndroidJavaObject javaObject, bool isStatic, string methodName, params object[] args)
    {
        if (javaObject != null)
        {
            if (isStatic)
            {
                return javaObject.CallStatic<T>(methodName, args);
            }

            return javaObject.Call<T>(methodName, args);
        }

        return default(T);
    }

    /// <summary>
    /// 调用Java代码，重载（2/8）
    /// </summary>
    public T CallJava<T>(AndroidJavaObject javaObject, bool isStatic, string methodName)
    {
        if (javaObject != null)
        {
            if (isStatic)
            {
                return javaObject.CallStatic<T>(methodName);
            }

            return javaObject.Call<T>(methodName);
        }

        return default(T);
    }

    /// <summary>
    /// 调用Java代码，重载（3/8）
    /// </summary>
    public void CallJava(AndroidJavaObject javaObject, bool isStatic, string methodName, params object[] args)
    {
        if (javaObject != null)
        {
            if (isStatic)
            {
                javaObject.CallStatic(methodName, args);
            }
            else
            {
                javaObject.Call(methodName, args);
            }
        }
    }

    /// <summary>
    /// 调用Java代码，重载（4/8）
    /// </summary>
    public void CallJava(AndroidJavaObject javaObject, bool isStatic, string methodName)
    {
        if (javaObject != null)
        {
            if (isStatic)
            {
                javaObject.CallStatic(methodName);
            }
            else
            {
                javaObject.Call(methodName);
            }
        }
    }

    /// <summary>
    /// 调用Java代码，重载（5/8）
    /// </summary>
    public T CallJava<T>(bool isStatic, string methodName, params object[] args)
    {
        return CallJava<T>(MainActivity, isStatic, methodName, args);
    }

    /// <summary>
    /// 调用Java代码，重载（6/8）
    /// </summary>
    public T CallJava<T>(bool isStatic, string methodName)
    {
        return CallJava<T>(MainActivity, isStatic, methodName);
    }

    /// <summary>
    /// 调用Java代码，重载（7/8）
    /// </summary>
    public void CallJava(bool isStatic, string methodName, params object[] args)
    {
        CallJava(MainActivity, isStatic, methodName, args);
    }

    /// <summary>
    /// 调用Java代码，重载（8/8）
    /// </summary>
    public void CallJava(bool isStatic, string methodName)
    {
        CallJava(MainActivity, isStatic, methodName);
    }
}