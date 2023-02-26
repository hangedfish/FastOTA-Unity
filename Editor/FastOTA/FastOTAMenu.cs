//
// Created by hangedfish (bravohangedman@outlook.com) on 2023/2/26.
//

using UnityEditor;
using UnityEngine;
using System.IO;

public static class FastOTAMenu
{
    [MenuItem("FastOTA/Copy Il2cpp API File for Sdk Build", false, 1)]
    private static void CopyIl2cppApiFile()
    {
        Debug.Log("UnityEditor: " + EditorApplication.applicationContentsPath);
        var apiFilePath = Path.Combine(EditorApplication.applicationContentsPath, "il2cpp/libil2cpp/il2cpp-api-functions.h");
        var targetPath = Path.Combine(Application.dataPath, "Editor/FastOTA/Android/cxx/il2cpp-api-functions.h");
        File.Copy(apiFilePath, targetPath);
    }
}

[InitializeOnLoad]
public static class EnableAndroidIl2cppStubMenuItem
{

    private const string MENU_NAME = "FastOTA/Enable Android IL2CPP Stub";

    private static bool enabled_;
    /// Called on load thanks to the InitializeOnLoad attribute
    static EnableAndroidIl2cppStubMenuItem()
    {
        EnableAndroidIl2cppStubMenuItem.enabled_ = EditorPrefs.GetBool(EnableAndroidIl2cppStubMenuItem.MENU_NAME, false);

        /// Delaying until first editor tick so that the menu
        /// will be populated before setting check state, and
        /// re-apply correct action
        EditorApplication.delayCall += () =>
        {
            PerformAction(EnableAndroidIl2cppStubMenuItem.enabled_);
        };
    }

    [MenuItem(EnableAndroidIl2cppStubMenuItem.MENU_NAME, false, 0)]
    private static void ToggleAction()
    {

        /// Toggling action
        PerformAction(!EnableAndroidIl2cppStubMenuItem.enabled_);
    }

    public static void PerformAction(bool enabled)
    {

        /// Set checkmark on menu item
        Menu.SetChecked(EnableAndroidIl2cppStubMenuItem.MENU_NAME, enabled);
        /// Saving editor state
        EditorPrefs.SetBool(EnableAndroidIl2cppStubMenuItem.MENU_NAME, enabled);

        EnableAndroidIl2cppStubMenuItem.enabled_ = enabled;

        /// Perform your logic here...
        if (EnableAndroidIl2cppStubMenuItem.enabled_)
        {
            Debug.Log("Enabled FastOTA_ENABLE_ANDROID_IL2CPP_STUB");
            EditorUserSettings.SetConfigValue("FastOTA_ENABLE_ANDROID_IL2CPP_STUB", "enabled");
        }
        else
        {
            Debug.Log("Disabled FastOTA_ENABLE_ANDROID_IL2CPP_STUB");
            EditorUserSettings.SetConfigValue("FastOTA_ENABLE_ANDROID_IL2CPP_STUB", "disabled");
        }
    }
}