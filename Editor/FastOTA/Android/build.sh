#! /bin/bash

if [ ! $ANDROID_NDK_HOME ]; then
    echo "Environment variable ANDROID_NDK_HOME is not set."
    exit 1
else
    echo "Use Android NDK path: $ANDROID_NDK_HOME"
fi

mkdir /tmp/build

echo "Build arm64-v8a"
mkdir -p lib/arm64-v8a
rm -rf /tmp/build/arm64-v8a

if ! cmake -B/tmp/build/arm64-v8a -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_VERSION=23 -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a -DCMAKE_ANDROID_NDK=$ANDROID_NDK_HOME -DCMAKE_ANDROID_STL_TYPE=c++_static cxx; 
then
    echo === CMakeOutput.log ===
    cat /tmp/build/arm64-v8a/CMakeFiles/CMakeOutput.log
    echo === CMakeError.log ===
    cat /tmp/build/arm64-v8a/CMakeFiles/CMakeError.log
    exit 1
fi

cmake --build /tmp/build/arm64-v8a

cp /tmp/build/arm64-v8a/libdlstub.so lib/arm64-v8a/libdlstub.so

echo "Build armeabi-v7a"

mkdir -p lib/armeabi-v7a                                          
rm -rf /tmp/build/armeabi-v7a

if ! cmake -B/tmp/build/armeabi-v7a -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_VERSION=23 -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_NDK=$ANDROID_NDK_HOME -DCMAKE_ANDROID_STL_TYPE=c++_static cxx; 
then
    echo === CMakeOutput.log ===
    cat /tmp/build/armeabi-v7a/CMakeFiles/CMakeOutput.log
    echo === CMakeError.log ===
    cat /tmp/build/armeabi-v7a/CMakeFiles/CMakeError.log
    exit 1
fi

cmake --build /tmp/build/armeabi-v7a

cp /tmp/build/armeabi-v7a/libdlstub.so lib/armeabi-v7a/libdlstub.so

echo "Build finished."
