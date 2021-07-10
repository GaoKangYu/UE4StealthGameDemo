// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	//创建对象
	LaunchPadComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadComp"));
	LaunchPadComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = LaunchPadComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	//绑定重叠后的事件
	LaunchPadComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::LaunchPadCompOverlap);

	LaunchStrength = 1500;
	LaunchPitchAngle = 35.0f;

}

void ALaunchPad::LaunchPadCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	//如果是玩家的actor与区域发生重叠
	AFPSCharacter* otherCharacter = Cast<AFPSCharacter>(OtherActor);
	if (otherCharacter)
	{
		otherCharacter->LaunchCharacter(LaunchVelocity, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics()) {
		//直接施加力
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	UE_LOG(LogTemp, Log, TEXT("Overlapped With LaunchPad!"));
}

