// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameStateBase.h"
#include "FPSPlayerController.h"


void AFPSGameStateBase::MultiCastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	////��������е�����actor����������
	//for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	//{
	//	APawn* Pawn = It->Get();
	//	//ֹͣ����pawn�Ŀ�����
	//	if (Pawn && Pawn->IsLocallyControlled())
	//	{
	//		Pawn->DisableInput(nullptr);
	//	}
	//}
	//�㲥���ͻ���ִ��������ɺ���ҿ������Ĳ���
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
