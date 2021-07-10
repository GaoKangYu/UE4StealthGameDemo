// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "FPSGameStateBase.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameStateBase::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		//�Ӵ���������������ֹͣ�ƶ����������ڶ�����Ϸ
		//InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);

			//����ҵ�����Чactor���ı��ӽ�
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				//�ڷ������ϵ�����һ���������ü���ǲ��Ǳ��ؿ��������ͻ��˵ı����ϲ��Ǳ��ؿ�����
				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					if (PC)
					{
						//��һ���ܹ����ƣ��ǿ�ܺ���������Ŀ���ӽǲ���ͻ��˴��ź�
						PC->SetViewTargetWithBlend(NewViewTarget, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewPointClass is Null"))
		}
	}

	AFPSGameStateBase* Gs = GetGameState<AFPSGameStateBase>();

	if (Gs)
	{
		Gs->MultiCastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
