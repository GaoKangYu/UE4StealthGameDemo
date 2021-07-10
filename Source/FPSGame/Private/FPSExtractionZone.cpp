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
	//创建对象并命名
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	//设置碰撞检测类型，仅询问
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//忽略所有渠道的碰撞
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//开启对人形体的碰撞响应
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//设置响应范围
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	//重叠组件默认不显示，此处更改为显示
	OverlapComp->SetHiddenInGame(false);
	//绑定重叠后的事件
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	OverlapCompDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("OverlapCompDecal"));
	OverlapCompDecal->DecalSize = FVector(200.0f);
	OverlapCompDecal->SetupAttachment(RootComponent);

}


void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//如果是玩家的actor与区域发生重叠
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr) 
	{
		return;
	}
	//并且玩家携带了目标，则通关
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

