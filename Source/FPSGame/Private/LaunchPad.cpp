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
	//��������
	LaunchPadComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadComp"));
	LaunchPadComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = LaunchPadComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	//���ص�����¼�
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

	//�������ҵ�actor���������ص�
	AFPSCharacter* otherCharacter = Cast<AFPSCharacter>(OtherActor);
	if (otherCharacter)
	{
		otherCharacter->LaunchCharacter(LaunchVelocity, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics()) {
		//ֱ��ʩ����
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	UE_LOG(LogTemp, Log, TEXT("Overlapped With LaunchPad!"));
}

