// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"


class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspiction,

	Alerted
};

UCLASS()

class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Content")
	UPawnSensingComponent* AIGuardSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	//使用这个变量的函数OnRep_GuardState可复用
	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIState GuardState;

	//当守卫状态发生改变，便会调用这一函数
	UFUNCTION()
	void OnRep_GuardState();

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//AI巡逻
	//以实例编辑，而不是以类
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	//meta只有在巡逻模式下才能给点分配值
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	AActor* CurrentPatorlPoint;

	void MoveToNextPatrolPoint();

};
