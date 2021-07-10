# UE4StealthGameDemo
基于Unreal4开发的潜行类游戏Demo
## 背景/需求
- 喜欢，想成为游戏行业从业者
- 本项目包含Windows-64Bit版Demo和源码

![demo_ui](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/demo.png)
<p align="center">demo截图</p>
## 文件结构

文件结构如下：

```
Road-Damage-Detection-System
├── demo(开发版demo下载地址)
├── screenshot(截图)
├── Source(源码)
```

## Actor介绍

- FPSAIGuard

对应BP_AIGuard,守卫，具有听觉与视觉，对Player的子弹有反应，看到，会在对应位置显示绿色DebugSphere，听到，会在对应位置显示红色DrawDebugSphere，其中一只守卫处于自动巡逻状态。

<div align=center><img width="430" height="280" src="https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BP_AIGuard%20Model.png"/></div>

<p align="center">AIGuard模型</p>

![AIGuard'sDetectationArea](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/AIGuard'sDetectationArea.png)

<p align="center">AIGuard视觉与听觉范围</p>

![BP_AIGuard Event List](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BP_AIGuard%20Event%20List.png)

<p align="center">BP_AIGuard事件列表（自动巡逻）</p>

![AIGuard And Target Point](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/AIGuard%20And%20Target%20Point.png)

<p align="center">关卡中的AIGuard及Target Point</p>

- FPSBlackHole

对应BP_BlackHole,黑洞，能吸引遮并摧毁蔽物（蓝色立方体）。

![BlackHoleModel](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BlackHoleModel.png)

<p align="center">关卡中的BlackHoleModel</p>

![BP_BlackHole](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BP_BlackHole.png)

<p align="center">BP_BlackHole</p>

![BlackHole](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BlackHole.gif)

<p align="center">BlackHole效果演示</p>

- FPSCharacter
- FPSExtractionZone
- FpsGameMode
- FPSGameStateBase
- FPSObjectiveActor
- LaunchPad
- FPsPlayerController
