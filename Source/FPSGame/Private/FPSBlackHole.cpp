// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//����壬��������������幹�ɺڶ�
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMeshComp"));
	//�������Ǹ����ϵ�����壬���ɼ�����˲���Ҫ��ײ���
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//��Ϊ�����
	RootComponent = MeshComp;

	//���Ƶģ������ڲ��������ͣ������С�������ڸ������
	InnerSphereComponents = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComponents->SetSphereRadius(100);
	//�������һ�±��ּ��ɣ�SetAttachParent���ɷ��ʣ�������setupattachment���õ�
	//InnerSphereComponents->SetAttachParent(MeshComp);
	InnerSphereComponents->SetupAttachment(MeshComp);

	//�����������¼���
	InnerSphereComponents->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerSphere);

	//ͬ���������ⲿ����
	OuterSphereComponents = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComponents->SetSphereRadius(3000);
	//OuterSphereComponents->SetAttachParent(MeshComp);
	OuterSphereComponents->SetupAttachment(MeshComp);


}


void AFPSBlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//��⵽�ⲿactor�����ڶ��ڲ����壬�ݻ��ⲿactor
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
//ÿ��ˢ��ʱ������е��ص��¼�
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Ԫ������ܹ���������ģ������
	TArray<UPrimitiveComponent*> OverlappingComps;
	//��ȡ���������ص�������
	OuterSphereComponents->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); ++i)
	{
		//�ж���Щ�����Ƿ�������ģ��
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			//�ǣ���ʼʩ�Ӿ�����
			const float SphereRadius = OuterSphereComponents->GetScaledSphereRadius();
			const float ForceStrength = -2000;//������ʾ��������
			//������뾶��Χ��ʩ�Ӿ�����
			//��ȡ����λ�ã�������뾶��Χ��ʩ�Ӿ����������Ĵ�С��ģ��Ч�����������䣬����ect�����Ƿ���ٱ仯
			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

