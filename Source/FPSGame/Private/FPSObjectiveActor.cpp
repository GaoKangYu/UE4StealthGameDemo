// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//ÿһ֡��ˢ��
	/*PrimaryActorTick.bCanEverTick = true;*/
	//�����������Ϊ�����
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	//����������������������������
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
	//����˿ͻ���ͬ������
	SetReplicates(true);

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	
	Super::BeginPlay();
	PlayEffects();
	
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAttached(PickupFX, SphereComp);
	//UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

//// Called every frame
//void AFPSObjectiveActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//������actor�����Ʒ�ص�ʱ������������ֻ�Խ�ɫ���actor����Ȥ��
	Super::NotifyActorBeginOverlap(OtherActor);
	//����Ч��
	PlayEffects();

	if (Role = ROLE_Authority)
	{

		UGameplayStatics::PlaySound2D(this, ObjectOverlapSound);
		//ǿתΪ��ɫ��ָ��
		AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);

		//ǿת�ɹ���
		if (MyCharacter)
		{
			//����Я����Ʒ״̬
			MyCharacter->bIsCarryObjective = true;
			//�ݻ���Ʒ���൱�ڱ�ʰȡ
			Destroy();
		}
	}
}

