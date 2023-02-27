FastOTA-Unity 是一个 稳定、高效、兼容性强 的 Unity Android libil2cpp.so 更新 SDK

* 稳定：不在运行时修改内存，无 Hook，不会产生内存修改失败导致的黑屏、闪退
* 高效：数据透传，无复杂的重定向逻辑，不产生额外的性能开销
* 兼容性强：兼容性与 Unity 编译配置一致，可在 TAPTAP、233乐园、摸摸鱼、闪玩 等基于 “沙盒容器” 或 “插件化” 技术的分发渠道中工作

已适配 Unity 2021、2022

> Google Play 政策禁止更新动态库，不要在 Google Play 渠道中使用

# 实现原理

创建一个 stub 动态库，反向代理 libil2cpp.so 的所有 il2cpp API，从而实现 libil2cpp.so 的灵活部署

# 集成和使用

## 集成
1. 将 Editor 和 Plugin 目录放入游戏工程
2. 参阅 [编译指引](Editor/FastOTA/README.md) 完成动态库编译

### 需要帮助

由于缺少 Windows 测试环境，暂不提供 Windows 环境的动态库构建脚本。如果有提交相关 PR，我会将其合并。

## 使用

建议游戏 APP 启动流程

1. SplashActivity

    1. 检查本地更新资源，使更新资源生效
    2. 启动 UnityPlayerActivity 进入游戏

2. UnityPlayerActivity
    
    联网检查游戏更新，如果游戏需要更新

    1. 下载和解压资源
    2. 重启游戏进程
        

更新资源至少包含
* 设备对应 ABI 的libil2cpp.so 文件
* global-metadata.dat 文件

### 使更新资源生效

你需要在游戏启动时，完成以下步骤，才可以使资源生效

* 使 global-metadata.dat 资源生效

    释放 global-metadata.dat 到对应的位置，覆盖原文件。global-metadata.dat 路径可以通过 `com.fastota.unity.UpSdk` 的 `GetGlobalMetadataFilePath` 静态方法获取。

* 使 libil2cpp.so 资源生效

    在 UnityPlayerActivity 启动之前，或在 `new UnityPlayer()` 之前，调用`com.fastota.unity.UpSdk` 的 `Register` 静态方法，传入更新资源中的 libil2cpp.so 文件的路径

# Q&A

Q1: AssetBundle 资源的更新呢

A1: AssetBundle 资源的更新比较适合游戏项目组自己搞定，之后的版本会考虑包含这部分内容

Q2: 为什么需要手动复制 "il2cpp-api-functions.h" 文件

A2：版权限制

# 与我联系

助理微信: gmtm3721

Email: bravohangedman@outlook.com

如果想请我喝杯咖啡，欢迎

Wechat

<img src=doc/img/wechat.JPG  width="150" height="150">


Alipay

<img src=doc/img/alipay.JPG  width="150" height="150">
