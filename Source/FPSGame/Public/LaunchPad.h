// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	//��Ҫʵ�廯��ʹ�þ�̬�ṹ��
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//�������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* LaunchPadComp;

	UFUNCTION()
		//�ص��¼���ʹ�����ú�����Ҫ������
	void LaunchPadCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//��������
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength;
	//����Ƕ�
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchPitchAngle;

	//��Ӷ�Ч
	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad")
	UParticleSystem* ActivateLaunchPadEffect;



public:	

};
