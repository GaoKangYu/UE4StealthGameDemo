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

	//ʹ����������ĺ���OnRep_GuardState�ɸ���
	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIState GuardState;

	//������״̬�����ı䣬��������һ����
	UFUNCTION()
	void OnRep_GuardState();

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//AIѲ��
	//��ʵ���༭������������
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	//metaֻ����Ѳ��ģʽ�²��ܸ������ֵ
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	AActor* CurrentPatorlPoint;

	void MoveToNextPatrolPoint();

};
