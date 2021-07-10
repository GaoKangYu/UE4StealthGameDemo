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
	//每一帧都刷新
	/*PrimaryActorTick.bCanEverTick = true;*/
	//网格体组件，为根组件
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	//球体组件，附加在了网格体组件上
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
	//服务端客户端同步销毁
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
	//当其他actor与该物品重叠时（上面设置了只对角色这个actor感兴趣）
	Super::NotifyActorBeginOverlap(OtherActor);
	//播放效果
	PlayEffects();

	if (Role = ROLE_Authority)
	{

		UGameplayStatics::PlaySound2D(this, ObjectOverlapSound);
		//强转为角色类指针
		AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);

		//强转成功则
		if (MyCharacter)
		{
			//更新携带物品状态
			MyCharacter->bIsCarryObjective = true;
			//摧毁物品，相当于被拾取
			Destroy();
		}
	}
}

