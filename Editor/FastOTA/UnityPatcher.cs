//
// Created by hangedfish (bravohangedman@outlook.com) on 2023/2/26.
//

using System;
using System.IO;

using UnityEditor;
using UnityEditor.Android;
using UnityEngine;

namespace FastOTA
{
    class UnityPatcher : IPostGenerateGradleAndroidProject
    {

        public int callbackOrder { get { return 0; } }
        public void OnPostGenerateGradleAndroidProject(string path)
        {
            Debug.Log("UnityPatcher.OnPostGenerateGradleAndroidProject at path: " + path);
            var jniLibsPath = Path.Combine(path, "src/main/jniLibs");

            string il2cppStubValue = EditorUserSettings.GetConfigValue("FastOTA_ENABLE_ANDROID_IL2CPP_STUB");
            if (il2cppStubValue == null || il2cppStubValue == "disabled")
            {
                Debug.Log("UnityPatcher disabled Android Il2cpp Stub");
                UninjectJniLib(jniLibsPath);

                return;
            }
            Debug.Log("UnityPatcher enabled Android Il2cpp Stub");

            InjectJniLib(jniLibsPath);
        }

        private static void InjectJniLib(string jniLibsPath)
        {

            foreach (var jniLibPath in Directory.GetDirectories(jniLibsPath))
            {
                var abiName = Path.GetFileName(jniLibPath);

                var stubAssetPath = Path.Combine(Application.dataPath, "Editor/FastOTA/Android/lib/" + abiName + "/libdlstub.so");
                var gameStubPath = Path.Combine(jniLibPath, "libdlstub.so");
                File.Copy(stubAssetPath, gameStubPath, true);

                var gameUnityPath = Path.Combine(jniLibPath, "libunity.so");
                Debug.Log("patch " + gameStubPath);
                ReplaceBytes(gameUnityPath, il2cppStrBytes, dlstubStrBytes);

                var gameMainPath = Path.Combine(jniLibPath, "libmain.so");
                Debug.Log("patch " + gameMainPath);
                ReplaceBytes(gameMainPath, libil2cppStrBytes, libdlstubStrBytes);
            }
        }

        private static void UninjectJniLib(string jniLibsPath)
        {

            foreach (var jniLibPath in Directory.GetDirectories(jniLibsPath))
            {
                var gameStubPath = Path.Combine(jniLibPath, "libdlstub.so");
                if (!File.Exists(gameStubPath))
                {
                    continue;
                }
                File.Delete(gameStubPath);

                var gameUnityPath = Path.Combine(jniLibPath, "libunity.so");
                ReplaceBytes(gameUnityPath, dlstubStrBytes, il2cppStrBytes);

                var gameMainPath = Path.Combine(jniLibPath, "libmain.so");
                ReplaceBytes(gameMainPath, libdlstubStrBytes, libil2cppStrBytes);
            }
        }

        // /il2cpp 2f696c3263707000
        static private byte[] il2cppStrBytes = new byte[] { 0x2f, 0x69, 0x6c, 0x32, 0x63, 0x70, 0x70, 0x00 };

        // /dlstub
        static private byte[] dlstubStrBytes = new byte[] { 0x2f, 0x64, 0x6c, 0x73, 0x74, 0x75, 0x62, 0x00 };

        // libil2cpp.so
        static private byte[] libil2cppStrBytes = new byte[] { 0x6C, 0x69, 0x62, 0x69, 0x6C, 0x32, 0x63, 0x70, 0x70, 0x2E, 0x73, 0x6F, 0x00 };

        // libdlstub.so
        static private byte[] libdlstubStrBytes = new byte[] { 0x6C, 0x69, 0x62, 0x64, 0x6C, 0x73, 0x74, 0x75, 0x62, 0x2E, 0x73, 0x6F, 0x00 };


        static public bool ReplaceBytes(string filename, byte[] targetBytes, byte[] newBytes)
        {
            try
            {
                var bytes = File.ReadAllBytes(filename);
                if (bytes == null)
                    return false;
                int idx = FindBytes(bytes, targetBytes);
                if (idx == -1)
                    return false;
                Debug.Log("idx: " + idx);
                for (int i = 0; i < targetBytes.Length; i++)
                {
                    bytes[idx + i] = newBytes[i];
                }
                File.WriteAllBytes(filename, bytes);
            }
            catch (Exception ex)
            {
                Debug.Log(ex.ToString());
                return false;
            }
            return true;
        }

        static private int FindBytes(byte[] src, byte[] find)
        {
            int index = -1;
            int matchIndex = 0;
            // handle the complete source array
            for (int i = 0; i < src.Length; i++)
            {
                if (src[i] == find[matchIndex])
                {
                    if (matchIndex == (find.Length - 1))
                    {
                        index = i - matchIndex;
                        break;
                    }
                    matchIndex++;
                }
                else if (src[i] == find[0])
                {
                    matchIndex = 1;
                }
                else
                {
                    matchIndex = 0;
                }

            }
            return index;
        }
    }

}