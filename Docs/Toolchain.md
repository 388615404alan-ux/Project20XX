# 工具方案：讨论稿

记录日期：2026-09-06，更新日期：2026-09-07。UE 5.8.2 已完成安装并通过项目编译与运行时冒烟测试；音频集成仍待兼容性验证后锁定。

用户已确认：主要 DAW 为 REAPER，熟练使用 Wwise，因此主要音频方案采用 REAPER + Wwise。音效由用户制作，不使用 AI 生成音效。音频设计细节后续讨论；引擎版本选择需核对所选 Wwise 集成的兼容性。当前电脑已确认为主力开发机。

## 起步工具

| 工具 | 用途 | 建议 |
| --- | --- | --- |
| Unreal Engine 5 与 Epic Games Launcher | 游戏运行、关卡、渲染、交互、打包 | UE 5.8.2 已安装至 D:\UE_5.8；项目编译和无界面启动已验证，Wwise 集成待验证 |
| Blender | 模型、UV、碰撞辅助网格、资产源文件 | 优先评估受支持的 LTS 版本，并实际验证到 UE 的导入流程 |
| Visual Studio 与对应的 C++/Windows SDK 组件 | 编译与调试游戏代码 | 匹配所选 UE 版本；安装 IDE 不等于编译组件已经齐全 |
| Git 与 Git LFS | 保存代码与大体积资产的版本 | 初期建议；需要另定远端存储、容量和独立备份方案 |
| REAPER | 声音设计、编辑、混音与导出 | 已确认；音效由用户亲自制作 |
| Wwise | 游戏事件、参数、空间声音与混音 | 已确认作为主要音频中间件；具体版本与 UE 集成待核对 |

2026-09-06 补充核对：Audiokinetic 官方公告列出 Wwise 2025.1.10 的 Unreal 5.6/5.7/5.8 集成，因此将 2025.1.10 作为新项目候选；现有 2025.1.0.8897 保持原样。公告不是本机集成测试结果。详细发布说明目前未能获取，Audiokinetic Launcher 的集成下载页面要求登录，尚未取得具体构建号或安装集成。来源：[Audiokinetic 官方公告](https://tw.linkedin.com/company/audiokinetic)。

无需为了启动项目同时引入多套 DCC、多个音频中间件或完整付费美术软件组合。贴图绘制、角色动画等专用工具根据实际资产需求再评估。

## 本机初步检查

迁移前已验证 UE 5.4.4/5.5.4/5.6.1、Wwise 2025.1.0.8897、MSVC 14.50.35717 和 Windows SDK 10.0.26100.0。三套旧 UE 现已卸载，UE 5.8.2 已安装并通过 `Project20XXEditor` 编译、Win64 平台验证和运行时加载。为解决 `SwarmInterface` 构建依赖，已向现有 Visual Studio 2026 添加 .NET Framework 4.8.1 SDK。详见 [开发环境检查](EnvironmentAudit.md)。

通过 Windows 软件安装记录发现以下条目，但尚未启动或验证其完整功能：

- REAPER 7.42、Ableton Live 12 Suite、Avid Pro Tools 24.3.1.162。
- Wwise Launcher 2025.1.0：这不是 Wwise Authoring/SDK 的版本确认。
- Epic Games Launcher：这不是 Unreal Engine 已安装的确认。
- Visual Studio Community 2026 18.2.1：C++ 工作负载与 Windows SDK 尚未检查。
- 本次安装记录检索未发现 Blender 或 Git 条目；不能据此认定未安装。

首次硬件查询受权限限制；权限变更后已成功检查：i5-13400F、RTX 5060 约 8GB 显存、32GB DDR4-3600。C、D 盘位于 NVMe SSD，检查时分别剩余 21.0、51.7 GiB；E 至 H 为机械硬盘分区。完整信息见 [主力开发机](Hardware.md)。

## 选型顺序

1. 主力开发机与硬件已确认；先安排 SSD 空间，再安装大型工具或导入大量资产。
2. REAPER 与 Wwise 已确认；检查本机 Wwise Authoring、SDK 及所需平台组件版本。
3. 核对音频集成对 UE 的支持版本，再锁定 UE、编译工具和中间件组合。
4. 验证 Blender 资产导入 UE，再锁定资产制作版本。
5. 配置版本管理与备份，创建最小游戏工程，并测试编译、声音播放和打包。

## 官方资料

- [UE 安装说明](https://dev.epicgames.com/documentation/unreal-engine/install-unreal-engine)
- [UE 硬件与软件要求](https://dev.epicgames.com/documentation/unreal-engine/hardware-and-software-specifications-for-unreal-engine)
- [UE 的 Visual Studio 配置](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine)
- [Blender LTS](https://www.blender.org/download/lts/)
- [Blender 系统要求](https://www.blender.org/download/requirements/)
- [Git LFS](https://git-lfs.com/)
- [Wwise 集成安装说明（版本示例，实际版本待选）](https://www.audiokinetic.com/library/2024.1.7_8863/?id=installation.html&source=UE4)
- [FMOD Unreal 集成](https://fmod.com/docs/2.03/unreal/welcome.html)
- [UE MetaSounds](https://dev.epicgames.com/documentation/en-us/unreal-engine/metasounds-the-next-generation-sound-sources-in-unreal-engine)
