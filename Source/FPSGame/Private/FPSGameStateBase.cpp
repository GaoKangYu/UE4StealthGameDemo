// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameStateBase.h"
#include "FPSPlayerController.h"


void AFPSGameStateBase::MultiCastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	////检查世界中的所有actor，包括敌人
	//for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	//{
	//	APawn* Pawn = It->Get();
	//	//停止所有pawn的控制器
	//	if (Pawn && Pawn->IsLocallyControlled())
	//	{
	//		Pawn->DisableInput(nullptr);
	//	}
	//}
	//广播给客户端执行任务完成后，玩家控制器的操作
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalPlayerController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			APawn* MyPawn = PC->GetPawn();

			if (MyPawn)
			{
				MyPawn->DisableInput(PC);
			}
		}
	}
}
