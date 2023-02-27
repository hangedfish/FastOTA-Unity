//
// Created by hangedfish (bravohangedman@outlook.com) on 2023/2/26.
//

package com.fastota.unity;

import android.system.Os;

public class UpSdk {
    public static void Register(String il2cppFilePath) {
        try {
            Os.setenv("FASTOAT_UPSDK_IL2CPP_FILEPATH", il2cppFilePath, true);
        } catch (Throwable e) {
            e.printStackTrace();
            return;
        }
    }

    public static String GetGlobalMetadataFilePath(Context ctx) {
        String filePath = GetUnityFilesDir(ctx) + "/dlstub/Metadata/global-metadata.dat";
        return filePath;
    }

    private static String GetUnityFilesDir(Context ctx) {
        File externalPath = ctx.getExternalFilesDir(null);
        File internalPath = ctx.getFilesDir();
        String state = Environment.getExternalStorageState();
        if (Environment.MEDIA_MOUNTED.equals(state) && externalPath.canRead() && externalPath.canWrite()) {
            return externalPath.getPath();
        }
        return internalPath.getPath();
    }

}