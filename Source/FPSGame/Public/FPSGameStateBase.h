// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	//网络组播，可靠连接
	//当函数经过服务器调用时，这一消息会发送至所有客户端，以在客户端运行该函数，服务器也会运行
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);
	
};
