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
	//�����鲥���ɿ�����
	//��������������������ʱ����һ��Ϣ�ᷢ�������пͻ��ˣ����ڿͻ������иú�����������Ҳ������
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);
	
};
