# 开发环境检查

日期：2026-09-06，更新日期：2026-09-07。初次检查范围：现有工具、引擎文件、编译组件与 Windows 平台校验。随后按用户要求卸载旧 UE，安装并验证 UE 5.8.2；最新状态见下文。

## UE 迁移进度

用户明确要求卸载旧引擎并安装 UE 5.8.2。

- UE 5.4.4、5.5.4、5.6.1 已通过 Epic Games Launcher 卸载。三套旧引擎的编辑器及 Build.version 均已不存在，启动器安装清单中也已没有旧 UE 主程序条目。
- UE 5.8.2（Changelist 56702186）已安装到 D:\UE_5.8，编辑器可执行文件与 Build.version 均已验证。
- 安装组件：引擎核心、模板和功能包、引擎源码。未勾选编辑器调试符号、MetaHuman 核心数据或额外移动/Linux 平台组件。选项页估计下载 11.665 GB、占用 29.517 GB；实际下载队列另有 Fab、Quixel Bridge 插件。
- 旧目录 D:\UE_5.4、D:\UE_5.6 和 C:\Program Files\Epic Games\UE_5.5 仍有插件/安装元数据残留，未手动删除。它们不再是完整引擎安装。
- 现有游戏工程、REAPER、Wwise 与 Visual Studio 未作迁移或删除。
- 已向 Visual Studio 2026 添加 .NET Framework 4.8.1 SDK，解决 `SwarmInterface` 规则依赖。
- `Project20XXEditor Win64 Development` 已完成 12/12 个构建动作，结果为 `Succeeded`。
- 无界面运行时测试成功加载 `SurvivalGameMode` 和 `/Engine/Maps/Templates/Template_Default`，Win64 平台报告 `VALID`，进程正常退出（0）。
- Wwise 集成仍未验证；下文 UE 5.6 的校验仅作为历史记录。

## 中文路径限制

当前工作区路径包含中文。UE 5.8.2/Visual Studio 14.50 在生成 PCH 时把该路径错误转码，导致 `C1083`。`subst` 盘符和 `-NoUBA` 均未解决，因为 UBT 会恢复真实路径。

源码主目录仍是当前工作区。已在纯英文路径的构建镜像中验证同一份源码；`Tools/Build-Editor.ps1` 会同步 `Config`、`Source` 和 `.uproject` 到 `D:\Project20XXBuild`，编译后把运行所需的 `Binaries` 复制回源码工程。长期方案是在开始大量 UE 资产制作前，把活跃 Unreal 工程迁移到不含中文的 SSD 路径。

## 迁移前已验证的安装（历史记录）

| 工具 | 版本 / 路径 | 验证范围 |
| --- | --- | --- |
| Unreal Engine | 5.6.1，D:\UE_5.6 | Build.version 与编辑器可执行文件存在；UBT Win64 平台检查通过 |
| Unreal Engine | 5.5.4，D:\Program Files\UE_5.5 | Build.version 与编辑器可执行文件存在 |
| Unreal Engine | 5.4.4，D:\UE_5.4 | Build.version 与编辑器可执行文件存在 |
| Wwise Authoring | 2025.1.0.8897，D:\Wwise2025.1.0.8897 | Wwise.exe 与 WwiseConsole.exe 的产品版本已读取 |
| Wwise SDK | 同一安装目录的 SDK | include、x64_vc170 与其他平台目录存在；未做链接测试 |
| Visual Studio Community | 2026 18.2.1 | vswhere 报告安装完整，包含 C++ 工具组件 |
| MSVC | 14.50.35717 | 编译工具目录存在 |
| Windows SDK | 10.0.26100.0 | SDK Include 目录存在；引擎平台检查通过 |

C:\Program Files\Epic Games\UE_5.5 存在旧插件安装记录，但未发现编辑器或 Build.version，不能计为另一套完整引擎。

## 尚未找到或验证

- Blender：已检查的安装记录、常见安装路径、命令 PATH、开始菜单未找到；不能排除其他目录的便携版本。
- Git/Git LFS：命令 PATH、常见安装路径、安装记录和开始菜单未找到；不能排除其他工具捆绑的版本。
- Wwise Unreal 集成：已检查三套引擎的 Marketplace 插件目录，未发现 Wwise 插件。未检查用户其他游戏项目中的项目级插件。
- 现有 Wwise 2025.1.0.8897 与 UE 5.6.1 对应集成包的精确兼容性尚未得到确认。官方文档查询未取得该版本有效说明，不应据此宣称已经兼容。

## 校验结果与限制

运行 UE 5.6.1 内置 UnrealBuildTool 的 ValidatePlatforms，限定 Win64，退出码 0：

```text
##PlatformValidate: Win64 VALID 10.0.22621.0
```

该输出中的 10.0.22621.0 来自引擎配置的 MainVersion，不是对本机已安装 SDK 目录版本的报告。测试仅表明引擎的 Windows 平台 SDK 校验通过，不证明 MSVC、游戏模块、Wwise 插件编译或最终打包通过。

本机 UE 的 Windows_SDK.json 将 MSVC 14.38.33130–14.38.99999 列为优选版本。当前仅检测到 14.50.35717。更高版本不自动等于不兼容；需要完整小型工程编译验证。若验证失败，优先补齐受支持的 VS 2022/MSVC 工具组合，保留现有 VS 2026。

## 起步建议

1. 用户已选定 UE 5.8.2；完成安装后验证新版本工具链。
2. 沿用 REAPER，保留现有 Wwise 2025.1；核实对应 UE 集成包。正式版本锁定前，评估该系列受支持的修订版。
3. 未发现其他 Blender 安装时，采用 Blender 5.2.1 LTS 作为候选，通过简单资产导入测试后锁定。
4. 补齐 Git 与 Git LFS，并配置项目级大文件规则。
5. 先安排 SSD 可用空间，再执行安装和完整工程构建。

初次检查未修改软件。后续用户已授权并执行上述 UE 迁移；未移动现有项目。

## 参考

- [UE 5.6 Visual Studio 配置](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine?application_version=5.6)
- [Blender LTS](https://www.blender.org/download/lts/)
- [Wwise Unreal 安装原则](https://www.audiokinetic.com/library/2025.1.3_9037/?id=installation.html&source=UE4)
- [Git LFS](https://git-lfs.com/)
