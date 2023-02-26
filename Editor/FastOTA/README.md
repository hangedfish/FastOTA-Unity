
适配 Unity 2021.3.19f1

# 目录结构
```
.
├── README.md
├── UnityPatcher.cs
├── build_android_dylib.sh
├── cxx
│   ├── CMakeLists.txt
│   ├── api.cpp
│   └──  api.h
└── java
    └── com
        └── fastota
            └── unity
                └── UpSdk.java
```

# 编译动态库

## 环境依赖

* NDK 23 以上版本
* CMAKE 21 以上版本

## 执行变异

* 复制 `il2cpp-api-functions.h` 到 `./Android/cxx` 目录
    * `il2cpp-api-function.h` 位于 ``${EditorApplication.applicationContentsPath}/il2cpp/libil2cpp` 目录
    * 可以通过点击 Unity Editor 菜单栏 "FastOTA/Copy Il2cpp API File for Sdk Build" ，自动完成复制

执行 `./Android/build.sh`，生成的动态库位于 `lib` 目录

```shell
ANDROID_NDK_HOME='/Volumes/iSCSI/ANDROID_SDK/ndk/25.2.9519653' sh ./build.sh
```

```
lib
├── arm64-v8a
│   └── libdlstub.so
└── armeabi-v7a
    └── libdlstub.so
```