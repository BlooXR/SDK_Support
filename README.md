# BlooXR SDK Official Support Repository
-----------------------------------------------------------
欢迎使用BlooXR 官方技术支持GitHub仓库。
BlooXR SDK基于OpenXR backend，当前为Pre-release Alpha版本，版本号V0.0.1。

##### Unity
Unity: Unity OpenXR app needs include the OpenXR Loader with Unity OpenXR plugin, refer: https://docs.unity3d.com/Packages/com.unity.xr.openxr@1.3/manual/features.html  (Custom Loader library) 

建议开发环境:
Unity Editor：2020.3.16f1c1及以上
OpenXR Plugin: 1.3及以上，建议最新版本
XR Interaction Toolkit 推荐使用最新版本2.1.1

##### Unreal 4
Unreal: Unreal OpenXR app needs include the OpenXRLoader with Unreal OpenXR plugin, refer: https://docs.unrealengine.com/4.26/en-US/SharingAndReleasing/XRDevelopment/OpenXR/

建议开发环境
Unreal引擎版本：427

### Supported Features
-----------------------------------------------------------
当前已支持feature
- 图形库支持：OpenGL ES，Vulkan
- 多视图渲染：支持Multi-view single pass/Multi-pass渲染模式
- input system：Oculus touch controller profile

### Underplan
-----------------------------------------------------------
- Controller 手柄调试环境支持
- Bloo Haptic 蓝鲸手柄特性：AAC瑞声振动马达支持
- Platform account linking 平台账户授权，用户免注册登录
- Device info设备/系统信息调用：音量/电量/麦克风/头戴唤醒/Bluetooth/WiFi
- Passthrough 灰度/彩色透视
- Boundary 安全区
- 截屏/录屏/投屏
- FFR 固定注视点渲染
