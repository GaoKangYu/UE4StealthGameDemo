// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;
//class UStaticMeshComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectOverlapSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;

	void PlayEffects();

public:	
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
