/*******************************************************************************
Copyright © 2021-2022 Bloo Technology Co., Ltd.All rights reserved.
*******************************************************************************/

using System.IO;
using UnityEditor;
using UnityEngine;

[InitializeOnLoad]
public class BXR_SDKSettingEditor : EditorWindow
{
    public static BXR_SDKSettingEditor window;
    public static string assetPath = "Assets/Resources/";
    GUIContent myTitleContent = new GUIContent();
    static Language language = Language.English;

    const BuildTarget recommendedBuildTarget = BuildTarget.Android;
    const UIOrientation recommendedOrientation = UIOrientation.LandscapeLeft;
    const bool recommendedRenderMode = false;

    public bool toggleBuildTarget = false;
    public bool toggleSetManifesst = false;
    public bool toggleOrientation = false;
    public bool toggleMTRendering = false;
    GUIStyle styleApply;

    static string[] strWindowName = { "BXR SDK Setting", "BXR SDK 设置" };

    string strseparate =
        "______________________________________________________________________________________________________________________________________________";

    string[] strNoticeText = { "Notice: Recommended project settings for BXR SDK", "注意：BXR SDK 推荐项目配置" };
    string[] strBtnChange = { "切换至中文", "Switch to English" };
    string[] strApplied = { "Applied", "已应用" };

    string[] strInformationText = { "Information:", "信息说明" };

    string[] strInfo1Text =
    {
        "1 Support Unity Version: Unity2019.4 and above",
        "1 支持Unity版本：Unity2019.4及以上版本"
    };

    string[] strInfo2Text =
    {
        "2 Player Setting: " + "  Default Orientation setting Landscape Left",
        "2 Player Setting: " + "  Default Orientation setting Landscape Left"
    };

    string[] strInfo3Text = { "3 Get the lastest version of SDK:", "3 获取最新版本的SDK:" };
    string[] strInfoURL = { "http://us-dev.bloovr.com/sdk", "http://dev.bloovr.com/sdk" };


    string[] strConfigurationText = { "Configuration:", "配置" };

    string[] strConfiguration1Text =
    {
        "1 current:             Build Target = {0}\n" +
        "   Recommended:  Build Target = {1}\n",
        "1 当前:             Build Target = {0}\n" +
        "   推荐:             Build Target = {1}\n"
    };

    private string[] quizHova =
    {
        "If selected, you will need to enter the APPID that is obtained from Pico Developer Platform after uploading the app for an entitlement check upon the app launch.",
        "如果勾选版权保护选项，并且填入正确的APPID，应用启动时会进行版权验证。可通过开发者平台获取APPID。"
    };

    private string[] strConfiguration2Text =
    {
        "2 current:             AndroidManifest Check = {0}\n" +
        "   Recommended:  AndroidManifest Check = true\n",
        "2 current:             AndroidManifest 检查 = {0}\n" +
        "   Recommended:  AndroidManifest 检查 = true\n",
    };

    private string[] quizYes =
    {
        "The APPID is required to run an Entitlement Check. Create / Find your APPID Here:",
        "应用版权保护要求填入正确的APPID，可通过网址创建或查看你的APPID：",
        "If you do not need user Entitlement Check, please uncheck it.",
        "如果不需要应用版权保护，请勿勾选"
    };

    private string getAppIDWebSite = "https://developer.pico-interactive.com/developer/overview";

    string[] strConfiguration3Text =
    {
        "3 current:             Orientation = {0}\n" +
        "    Recommended:  Orientation = {1}\n",
        "3 当前:             Orientation = {0}\n" +
        "    推荐:             Orientation = {1}\n"
    };

    string[] strConfiguration4Text =
    {
        "4 current:             Multithreaded Rendering = {0}\n" +
        "    Recommended:  Multithreaded Rendering = {1}\n",
        "4 当前:             Multithreaded Rendering = {0}\n" +
        "    推荐:             Multithreaded Rendering = {1}\n"
    };

    string[] strBtnApply = { "Apply", "应用" };
    string[] strBtnClose = { "Close", "关闭" };

    static BXR_SDKSettingEditor()
    {
        EditorApplication.update += Update;
    }

    static void Update()
    {
        bool allApplied = IsAllApplied();
        bool showWindow = !allApplied;
        if (IsIgnoreWindow())
        {
            showWindow = false;
        }

        if (showWindow)
        {
            ShowSettingWindow();
        }

        EditorApplication.update -= Update;
    }

    public static bool IsIgnoreWindow()
    {
        string path = assetPath + typeof(BXR_SDKSettingAsset).ToString() + ".asset";
        if (File.Exists(path))
        {
            BXR_SDKSettingAsset asset = AssetDatabase.LoadAssetAtPath<BXR_SDKSettingAsset>(path);
            return asset.ignoreSDKSetting;
        }

        return false;
    }

    static void ShowSettingWindow()
    {
        if (window != null)
            return;
        window = (BXR_SDKSettingEditor)GetWindow(typeof(BXR_SDKSettingEditor), true, strWindowName[(int)language],
            true);
        window.autoRepaintOnSceneChange = true;
        window.minSize = new Vector2(820, 520);
    }

    public void OnGUI()
    {
        myTitleContent.text = strWindowName[(int)language];
        if (window != null)
        {
            window.titleContent = myTitleContent;
        }

        ShowNoticeTextAndChangeBtn();

        GUIStyle styleSlide = new GUIStyle();
        styleSlide.normal.textColor = Color.white;
        GUILayout.Label(strseparate, styleSlide);

        GUILayout.Label(strInformationText[(int)language]);
        GUILayout.Label(strInfo1Text[(int)language]);
        GUILayout.Label(strInfo2Text[(int)language]);
        GUILayout.Label(strInfo3Text[(int)language]);
        string strURL = strInfoURL[(int)language];
        GUIStyle style = new GUIStyle();
        style.normal.textColor = new Color(0, 122f / 255f, 204f / 255f);
        if (GUILayout.Button("    " + strURL, style, GUILayout.Width(200)))
        {
            Application.OpenURL(strURL);
        }

        GUILayout.Label(strseparate, styleSlide);

        GUILayout.Label(strConfigurationText[(int)language]);

        string strinfo1 = string.Format(strConfiguration1Text[(int)language], EditorUserBuildSettings.activeBuildTarget,
            recommendedBuildTarget);
        EditorConfigurations(strinfo1, EditorUserBuildSettings.activeBuildTarget == recommendedBuildTarget,
            ref toggleBuildTarget);

        string strinfo2 = string.Format(strConfiguration2Text[(int)language], CheckAndroidManifest());
        EditorConfigurations(strinfo2, CheckAndroidManifest(), ref toggleSetManifesst);

        string strinfo3 = string.Format(strConfiguration3Text[(int)language],
            PlayerSettings.defaultInterfaceOrientation, recommendedOrientation);
        EditorConfigurations(strinfo3, PlayerSettings.defaultInterfaceOrientation == recommendedOrientation,
            ref toggleOrientation);

        string strinfo4 = string.Format(strConfiguration4Text[(int)language],
            PlayerSettings.GetMobileMTRendering(BuildTargetGroup.Android), recommendedRenderMode);
        EditorConfigurations(strinfo4,
            PlayerSettings.GetMobileMTRendering(BuildTargetGroup.Android) == recommendedRenderMode,
            ref toggleMTRendering);

        EditorGUILayout.Space();
        EditorGUILayout.BeginHorizontal();
        EditorGUILayout.LabelField("", GUILayout.Width(200));

        if (IsAllApplied())
        {
            styleApply = new GUIStyle("ObjectPickerBackground");
            styleApply.alignment = TextAnchor.MiddleCenter;
        }
        else
        {
            styleApply = new GUIStyle("LargeButton");
            styleApply.alignment = TextAnchor.MiddleCenter;
        }

        if (GUILayout.Button(strBtnApply[(int)language], styleApply, GUILayout.Width(100), GUILayout.Height(30)))
        {
            EditorApplication.delayCall += OnClickApply;
        }

        styleApply = null;

        EditorGUILayout.LabelField("", GUILayout.Width(200));
        if (GUILayout.Button(strBtnClose[(int)language], GUILayout.Width(100), GUILayout.Height(30)))
        {
            OnClickClose();
        }

        EditorGUILayout.EndHorizontal();
    }

    public void OnClickApply()
    {
        if (toggleOrientation && PlayerSettings.defaultInterfaceOrientation != recommendedOrientation)
        {
            PlayerSettings.defaultInterfaceOrientation = recommendedOrientation;
        }

        if (toggleSetManifesst)
        {
            ApplyAndroidManifest();
        }

        if (toggleBuildTarget && EditorUserBuildSettings.activeBuildTarget != recommendedBuildTarget)
        {
            EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android, recommendedBuildTarget);
            EditorUserBuildSettings.selectedBuildTargetGroup = BuildTargetGroup.Android;
        }

        if (toggleMTRendering && PlayerSettings.GetMobileMTRendering(BuildTargetGroup.Android) != recommendedRenderMode)
        {
            PlayerSettings.SetMobileMTRendering(BuildTargetGroup.Android, recommendedRenderMode);
        }

        BXR_SDKSettingAsset asset;
        string assetPath = BXR_SDKSettingEditor.assetPath + typeof(BXR_SDKSettingAsset).ToString() + ".asset";
        if (File.Exists(assetPath))
        {
            asset = AssetDatabase.LoadAssetAtPath<BXR_SDKSettingAsset>(assetPath);
        }
        else
        {
            asset = new BXR_SDKSettingAsset();
            ScriptableObjectUtility.CreateAsset<BXR_SDKSettingAsset>(asset, BXR_SDKSettingEditor.assetPath);
        }

        AssetDatabase.SaveAssets();
        AssetDatabase.Refresh();
    }

    void OnClickClose()
    {
        bool allApplied = IsAllApplied();
        if (allApplied)
        {
            Close();
        }
        else
        {
            BXR_SettingMessageBoxEditor.Init(language);
        }
    }

    public static bool IsAllApplied()
    {
        bool notApplied = (EditorUserBuildSettings.activeBuildTarget != recommendedBuildTarget)
                          || !CheckAndroidManifest()
                          || (PlayerSettings.defaultInterfaceOrientation != recommendedOrientation)
                          || PlayerSettings.GetMobileMTRendering(BuildTargetGroup.Android) != recommendedRenderMode;

        if (!notApplied)
            return true;
        else
            return false;
    }

    private static bool CheckAndroidManifest()
    {
        string manifestPath = Application.dataPath + "/Plugins/Android/AndroidManifest.xml";
        if (File.Exists(manifestPath))
        {
            string xmlStr = File.ReadAllText(manifestPath);
            if (xmlStr.Contains("com.qualcomm.qti.openxrruntime") &&
                xmlStr.Contains("org.khronos.openxr.permission.OPENXR") &&
                xmlStr.Contains("com.qti.intent.category.SNAPDRAGON_VR")) return true;
        }

        return false;
    }

    private void ApplyAndroidManifest()
    {
        string str00 = "<application";
        string str01 =
            "<queries>\n<package android:name=\"com.qualcomm.qti.openxrruntime\"/>\n</queries>\n<application";

        string str10 = "</application>";
        string str11 = "</application>\n<uses-permission android:name=\"org.khronos.openxr.permission.OPENXR\" />";

        string str20 = "android.intent.action.MAIN\" />";
        string str200 = "android.intent.action.MAIN\"/>";
        string str21 =
            "android.intent.action.MAIN\" />\n<category android:name=\"com.qti.intent.category.SNAPDRAGON_VR\"/>";

        string rootPath = Application.dataPath + "/Plugins/Android";
        string manifestPath = rootPath + "/AndroidManifest.xml";
        if (!File.Exists(manifestPath))
        {
            var ms = MonoScript.FromScriptableObject(this);
            var path = AssetDatabase.GetAssetPath(ms);
            path = Path.GetDirectoryName(path);
            string amPath = path + "/AndroidManifest.xml";
            if (File.Exists(amPath))
            {
                if (!Directory.Exists(rootPath)) Directory.CreateDirectory(rootPath);
                File.Copy(amPath, manifestPath);
            }
            else
            {
                Debug.LogError("AndroidManifest.xml temp is not exists!");
            }
        }
        else
        {
            string xmlStr = File.ReadAllText(manifestPath);
            if (!xmlStr.Contains("com.qualcomm.qti.openxrruntime"))
            {
                xmlStr = xmlStr.Replace(str00, str01);
            }

            if (!xmlStr.Contains("org.khronos.openxr.permission.OPENXR"))
            {
                xmlStr = xmlStr.Replace(str10, str11);
            }

            if (!xmlStr.Contains("com.qti.intent.category.SNAPDRAGON_VR"))
            {
                xmlStr = xmlStr.Replace(str20, str21);
                xmlStr = xmlStr.Replace(str200, str21);
            }

            File.WriteAllText(manifestPath, xmlStr);
        }
    }

    void EditorConfigurations(string strConfiguration, bool enable, ref bool toggle)
    {
        EditorGUILayout.BeginHorizontal();

        GUILayout.Label(strConfiguration, GUILayout.Width(500));

        GUIStyle styleApplied = new GUIStyle();
        styleApplied.normal.textColor = Color.green;
        if (enable)
        {
            GUILayout.Label(strApplied[(int)language], styleApplied);
        }
        else
        {
            toggle = EditorGUILayout.Toggle(toggle);
        }

        EditorGUILayout.EndHorizontal();
    }

    void ShowNoticeTextAndChangeBtn()
    {
        EditorGUILayout.BeginHorizontal();

        GUIStyle styleNoticeText = new GUIStyle();
        styleNoticeText.alignment = TextAnchor.UpperCenter;
        styleNoticeText.fontSize = 20;
        GUILayout.Label(strNoticeText[(int)language], styleNoticeText);

        if (GUILayout.Button(strBtnChange[(int)language], GUILayout.Width(150), GUILayout.Height(30)))
        {
            SwitchLanguage();
        }

        EditorGUILayout.EndHorizontal();
    }

    void SwitchLanguage()
    {
        if (language == Language.Chinese)
            language = Language.English;
        else if (language == Language.English)
            language = Language.Chinese;
    }
}

public enum Language
{
    English,
    Chinese,
}

public class BXR_SettingMessageBoxEditor : EditorWindow
{
    static BXR_SettingMessageBoxEditor myWindow;
    static Language language = Language.English;
    static string[] strWindowName = { "Ignore the recommended configuration", "忽略推荐配置" };

    string[] strTipInfo =
    {
        "                                   No more prompted \n" +
        "             You can get recommended configuration from  \n" +
        "                            Development documentation.",
        "                               点击\"忽略\"后,不再提示！\n" +
        "                       可从开发者文档中获取推荐配置说明  \n"
    };

    string[] strBtnIgnore = { "Ignore", "忽略" };
    string[] strBtnCancel = { "Cancel", "取消" };

    public static void Init(Language language)
    {
        BXR_SettingMessageBoxEditor.language = language;
        myWindow = (BXR_SettingMessageBoxEditor)GetWindow(typeof(BXR_SettingMessageBoxEditor), true,
            strWindowName[(int)language], true);
        myWindow.autoRepaintOnSceneChange = true;
        myWindow.minSize = new Vector2(360, 200);
        myWindow.Show(true);
        Rect pos;
        if (BXR_SDKSettingEditor.window != null)
        {
            Rect frect = BXR_SDKSettingEditor.window.position;
            pos = new Rect(frect.x + 300, frect.y + 200, 200, 140);
        }
        else
        {
            pos = new Rect(700, 400, 200, 140);
        }

        myWindow.position = pos;
    }

    void OnGUI()
    {
        for (int i = 0; i < 10; i++)
        {
            EditorGUILayout.Space();
        }

        GUILayout.Label(strTipInfo[(int)language]);

        for (int i = 0; i < 3; i++)
        {
            EditorGUILayout.Space();
        }

        EditorGUILayout.BeginHorizontal();
        EditorGUILayout.LabelField("", GUILayout.Width(20));
        if (GUILayout.Button(strBtnIgnore[(int)language], GUILayout.Width(100), GUILayout.Height(30)))
        {
            OnClickIgnore();
        }

        EditorGUILayout.LabelField("", GUILayout.Width(50));
        if (GUILayout.Button(strBtnCancel[(int)language], GUILayout.Width(130), GUILayout.Height(30)))
        {
            OnClickCancel();
        }

        EditorGUILayout.EndHorizontal();
    }

    void OnClickIgnore()
    {
        SaveAssetDataBase();
        BXR_SDKSettingEditor.window.Close();
        Close();
    }

    private void SaveAssetDataBase()
    {
        BXR_SDKSettingAsset asset;
        string assetPath = BXR_SDKSettingEditor.assetPath + typeof(BXR_SDKSettingAsset).ToString() + ".asset";
        if (File.Exists(assetPath))
        {
            asset = AssetDatabase.LoadAssetAtPath<BXR_SDKSettingAsset>(assetPath);
        }
        else
        {
            asset = new BXR_SDKSettingAsset();
            ScriptableObjectUtility.CreateAsset<BXR_SDKSettingAsset>(asset, BXR_SDKSettingEditor.assetPath);
        }

        asset.ignoreSDKSetting = true;

        EditorUtility.SetDirty(asset);
        AssetDatabase.SaveAssets();
        AssetDatabase.Refresh();
    }

    void OnClickCancel()
    {
        Close();
    }
}

[InitializeOnLoad]
public class BXR_SDKAndroidManifestSetting
{
    [InitializeOnLoadMethod]
    static void BxrSDKManifestSettings()
    {
    }
}

public static class ScriptableObjectUtility
{
    public static void CreateAsset<T>(T classdata, string path) where T : ScriptableObject
    {
        if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }

        string assetPathAndName = AssetDatabase.GenerateUniqueAssetPath(path + typeof(T).ToString() + ".asset");

        AssetDatabase.CreateAsset(classdata, assetPathAndName);

        AssetDatabase.SaveAssets();
        AssetDatabase.Refresh();
    }
}