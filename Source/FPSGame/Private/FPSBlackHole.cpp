// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//组合体，用于组合内外球体构成黑洞
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMeshComp"));
	//本质上是概念上的组合体，不可见，因此不需要碰撞检测
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//作为根组件
	RootComponent = MeshComp;

	//类似的，定义内部球体类型，给予大小，依附于父组合体
	InnerSphereComponents = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComponents->SetSphereRadius(100);
	//待会测试一下表现即可，SetAttachParent不可访问，单纯供setupattachment调用的
	//InnerSphereComponents->SetAttachParent(MeshComp);
	InnerSphereComponents->SetupAttachment(MeshComp);

	//将内球体与事件绑定
	InnerSphereComponents->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerSphere);

	//同样，定义外部球体
	OuterSphereComponents = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComponents->SetSphereRadius(3000);
	//OuterSphereComponents->SetAttachParent(MeshComp);
	OuterSphereComponents->SetupAttachment(MeshComp);


}


void AFPSBlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//检测到外部actor碰到黑洞内部球体，摧毁外部actor
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
//每次刷新时检测所有的重叠事件
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//元组件，能够接受物理模拟属性
	TArray<UPrimitiveComponent*> OverlappingComps;
	//获取与外球体重叠的物体
	OuterSphereComponents->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); ++i)
	{
		//判断这些物体是否有物理模拟
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			//是，开始施加径向力
			const float SphereRadius = OuterSphereComponents->GetScaledSphereRadius();
			const float ForceStrength = -2000;//负数表示由外向内
			//在球体半径范围内施加径向力
			//获取物体位置，在球体半径范围内施加径向力，力的大小，模拟效果（持续不变，线性ect），是否加速变化
			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

