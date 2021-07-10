# UE4StealthGameDemo
基于Unreal4.26开发的潜行类游戏Demo，支持多人游戏（Replication）
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

对应BP_AIGuard,守卫，具有听觉与视觉，对Player的子弹有反应，看到，头顶出现“!”，任务失败，会在对应位置显示绿色DebugSphere，听到，头顶出现“?”，表示警觉，会在对应位置显示红色DrawDebugSphere，其中一只守卫处于自动巡逻状态。

<div align=center><img width="430" height="280" src="https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BP_AIGuard%20Model.png"/></div>

<p align="center">AIGuard模型</p>

![AIGuard'sDetectationArea](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/AIGuard'sDetectationArea.png)

<p align="center">AIGuard视觉与听觉范围</p>

![BP_AIGuard Event List](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/BP_AIGuard%20Event%20List.png)

<p align="center">BP_AIGuard事件列表</p>

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

可操作角色，基于FPS模板，可开枪发射子弹，拥有是否持有目标物体（FPSObjectiveActor）这一状态。

<div align=center><img width="445" height="345" src="https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/Player.png"/></div>

<p align="center">BP_Player</p>

- FPSExtractionZone

撤离区域，当玩家未携带目标物体通过时发出无效音效，持有目标物体时发出任务成功音效并触发任务成功逻辑。

![ExtractionZone](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/ExtractionZone.png)

<p align="center">关卡中的ExtractionZone</p>

![ExtractionZoneEffect](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/ExtractionZone.gif)

<p align="center">ExtractionZoneUnderMissionSuccess</p>

- FPSObjectiveActor

目标物体，持续散发粒子特效，能够被玩家拾取。

![ObjectInLevel](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/ObjectInLevel.png)

<p align="center">关卡中的ObjectInLevel</p>

![Object](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/Object.gif)

<p align="center">拾取Object</p>

- LaunchPad

能够弹起玩家或遮蔽物，到达较高的区域。

![LaunchPad](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/LaunchPad.png)

<p align="center">LaunchPad</p>

![LaunchPadEffect](https://github.com/GaoKangYu/UE4StealthGameDemo/blob/main/screenshot/LaunchPadEffect.gif)

<p align="center">LaunchPad效果演示</p>
