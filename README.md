# Project20XX

项目建立日期：2026-09-06。Project20XX 是临时目录名，不是正式游戏名称。

## 已确认的方向

- 背景：20xx 年，全球爆发核战争。
- 核心主题：主角在核袭击及其后果中求生。
- 用户希望制作大型生存游戏，并以商业级质量为目标。
- 用户是游戏音频设计师，不精通程序与画面制作。
- 音频工具确定为 REAPER 与 Wwise；用户熟练使用 Wwise，音效由用户亲自制作，不使用 AI 生成音效。音频细节后续讨论。
- 当前阶段：UE 5.8.2 技术原型，正在验证避难所场景与交互。

## 文档

- [工具方案](Docs/Toolchain.md)：用途、选型建议与待验证事项。
- [主力开发机](Docs/Hardware.md)：硬件、磁盘空间与制作环境建议。
- [开发环境检查](Docs/EnvironmentAudit.md)：实际安装版本、平台校验结果和待补齐事项。
- [项目起点](Docs/ProjectBrief.md)：已确认内容、建议与尚未决定的问题。

## 目录用途

| 目录 | 内容 |
| --- | --- |
| Docs | 设计、决策、技术与制作说明 |
| Game | 确定引擎版本后创建的游戏工程 |
| SourceAssets/Blender | 可编辑模型与场景源文件 |
| SourceAssets/Textures | 贴图及材质源文件 |
| Audio/Sessions | DAW 工程与制作源文件 |
| Audio/Exports | 供游戏使用的音频导出文件 |
| Audio/Middleware | 确定方案后建立的音频中间件工程 |
| References | 用户提供的参考资料 |
| Tools | 项目专用自动化与资产处理脚本 |
| Builds | 可以独立运行的游戏构建 |

## 当前进展

- UE 5.8.2 已安装在 `D:\UE_5.8`，三套旧 UE 主程序已卸载。
- 已补齐 `.NET Framework 4.8.1 SDK`，UE 5.8 编辑器目标可以编译。
- 已创建 `Game/Project20XX` C++ 工程和第一版避难所灰盒玩法。
- 已实现第一人称移动、视线交互、防爆门和物资拾取。
- `Project20XXEditor Win64 Development` 已完整编译，运行时冒烟测试退出码为 0。
- 当前中文工作区会触发 MSVC 路径转码问题；源码仍以此目录为准，构建脚本通过 D 盘英文镜像编译。

出生点修复已经编译成功；修复后的可见画面、门和物资交互仍待实机验收。下一步是完成该检查，然后建立项目级关卡、加入照明和第一套生存状态。

## 构建与运行

需要单独安装 Unreal Engine 5.8.2、兼容的 Visual Studio C++ 工具链、Windows SDK 和 .NET Framework SDK。本仓库不包含引擎、编译产物或缓存。

Windows PowerShell 中，在仓库根目录运行：

```powershell
.\Tools\Build-Editor.ps1 -EngineRoot 'D:\UE_5.8' -MirrorRoot 'D:\Project20XXBuild'
```

`MirrorRoot` 必须是专用于此项目的英文路径：脚本会替换该目录中的 `Config` 和 `Source`。当前脚本用于现有纯代码原型；引入项目级 Content 或 Plugins 后需扩展同步范围。

编译成功后打开 `Game/Project20XX/Project20XX.uproject`，在编辑器中点击 Play。操作为 WASD 移动、鼠标观察、空格跳跃、E 交互。当前使用引擎自带模板地图，尚未打包为独立游戏；音频尚未接入 Wwise。
