using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 依附于unity主线程，但不处理具体gameobject逻辑的数据单例类
/// </summary>
/// <typeparam name="T"></typeparam>
public class MonoSingleton<T> : MonoBehaviour where T : MonoSingleton<T>
{
    private static T instance;
    private static bool isQuit = false;

    public static T Instance
    {
        get
        {
            if (instance == null)
            {
                if (!isQuit)
                {
                    GameObject go = GameObject.Find("MonoSingleton");
                    if (go == null)
                    {
                        go = new GameObject("MonoSingleton");
                        DontDestroyOnLoad(go);
                    }

                    instance = go.GetComponent<T>();
                    if (instance == null) instance = go.AddComponent<T>();
                }
            }

            return instance;
        }
    }

    private void OnApplicationQuit()
    {
        isQuit = true;
    }

    protected virtual void Awake()
    {
    }

    protected virtual void Start()
    {
    }

 /*   protected virtual void Update()
    {
    }*/

    protected virtual void OnDestroy()
    {
    }
}