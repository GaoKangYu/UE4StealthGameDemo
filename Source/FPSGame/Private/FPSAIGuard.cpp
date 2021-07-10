// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIGuardSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("AIGuardSensingComp"));

	//绑定听、视事件
	AIGuardSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);

	AIGuardSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Green, false, 10.0f);

	AFPSGameMode* MyGM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (MyGM)
	{
		MyGM->CompleteMission(SeenPawn, false);
	}

	SetGuardState(EAIState::Alerted);

	//看到pawn，停止移动
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);

	//make guard turn to noise source
	//change location to rotation
	FVector Direction = Location - GetActorLocation();

	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();

	//rotation combs of pitch(up down)   yaw(left  right)    roll(斜)
	//no need to turn roll or pitch
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
 
	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);

	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f, false);

	SetGuardState(EAIState::Suspiction);

	//听到声音，停止移动
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
}

void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);

	//闲置状态时，如果需要巡逻，则巡逻
	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

//客户端上调用函数
void AFPSAIGuard::OnRep_GuardState()
{
	OnStateChanged(GuardState);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}
	GuardState = NewState;

	//服务器得到该变量后，客户端自动触发，获得该变量，从而触发函数
	OnRep_GuardState();
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatorlPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatorlPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();
		//实现往返
		if (DistanceToGoal < 75)
		{
			MoveToNextPatrolPoint();
		}
	}

}

void AFPSAIGuard::MoveToNextPatrolPoint()
{
	if (CurrentPatorlPoint == nullptr || CurrentPatorlPoint == SecondPatrolPoint)
	{
		CurrentPatorlPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatorlPoint = SecondPatrolPoint;
	}
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatorlPoint);
	
}

//
void AFPSAIGuard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, GuardState);
}

