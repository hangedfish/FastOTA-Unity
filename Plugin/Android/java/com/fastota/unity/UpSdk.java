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

}