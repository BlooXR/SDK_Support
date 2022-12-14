# BlooXR SDK Official Support Repository
-----------------------------------------------------------
欢迎使用BlooXR 官方技术支持GitHub仓库。
BlooXR SDK基于OpenXR backend，当前为Beta版本，支持Unity项目开发，支持UE4项目开发
### 开发环境
-----------------------------------------------------------
#### Unity
- Unity: Unity OpenXR app needs include the OpenXR Loader with Unity OpenXR plugin, refer: https://docs.unity3d.com/Packages/com.unity.xr.openxr@1.3/manual/features.html  (Custom Loader library) 
- Unity Editor：2020.3.16f1c1及以上
- OpenXR Plugin: 1.3及以上，建议最新版本
- XR Interaction Toolkit 推荐使用最新版本2.1.1

#### Unreal 4
- Unreal: Unreal OpenXR app needs include the OpenXRLoader with Unreal OpenXR plugin, refer: https://docs.unrealengine.com/4.26/en-US/SharingAndReleasing/XRDevelopment/OpenXR/
- Unreal引擎版本：4.27, 4.26

#### Android
- 版本：Android 12


### Supported Features 已支持
-----------------------------------------------------------
Unity已支持features
- 图形库支持：OpenGL ES，Vulkan
- 多视图渲染：支持Multi-view single pass/Multi-pass渲染模式
- input system：Oculus touch controller profile, BlooXR touch controller profile
- Controller 手柄调试环境支持
- Bloo Haptic 蓝鲸手柄特性：AAC瑞声振动马达支持

Unreal已支持features
- 图形库支持：Vulkan
- 多视图渲染
- OpenXR input system with controller VR手柄交互
- Bloo controller haptic 蓝鲸手柄震动定义工具

### Under plan 计划中
-----------------------------------------------------------
- Platform account linking 平台账户授权，用户免注册登录
- Device info设备/系统信息调用：音量/电量/麦克风/头戴唤醒/Bluetooth/WiFi
- Passthrough 灰度/彩色透视
- Boundary 安全区
- 截屏/录屏/投屏
- FFR 固定注视点渲染
