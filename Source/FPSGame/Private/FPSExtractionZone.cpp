// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	//������������
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	//������ײ������ͣ���ѯ��
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//����������������ײ
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//���������������ײ��Ӧ
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//������Ӧ��Χ
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	//�ص����Ĭ�ϲ���ʾ���˴�����Ϊ��ʾ
	OverlapComp->SetHiddenInGame(false);
	//���ص�����¼�
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	OverlapCompDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("OverlapCompDecal"));
	OverlapCompDecal->DecalSize = FVector(200.0f);
	OverlapCompDecal->SetupAttachment(RootComponent);

}


void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�������ҵ�actor���������ص�
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr) 
	{
		return;
	}
	//�������Я����Ŀ�꣬��ͨ��
	if (MyPawn->bIsCarryObjective)
	{
		AFPSGameMode* MyGM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (MyGM)
		{
			MyGM->CompleteMission(MyPawn, true);
			UGameplayStatics::PlaySound2D(this, MissionCompleteSound);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectMissingSound);
	}
	UE_LOG(LogTemp, Log, TEXT("Overlapped With Extraction Zone!"));
}

