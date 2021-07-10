// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

//�����ڶ���
//Ŀ�ģ�����cpp�������Эͬ�߼�������ʵ�ֲ��ֹ���

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
//�ڶ���һ����ʵ����ӵĶ�������Ǽ̳���actor��
class FPSGAME_API AFPSBlackHole : public AActor
{
	//�����Ϊ�궨��ע�����
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//���캯��
	AFPSBlackHole();

protected:
	//�����е��������Ҫ��������ͼ�༭
	// ���������ʾ���actor
	//Ϊ����ʾ���actor��Ҫ�������������������Ƕ��徲̬�����壬���ڳ������actor
	//U������꣬��������ͼ��Ȩ��Ϊ�ɼ������ɱ༭
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//��󣬺ڶ���������֣��ڲ�����ʵ����Դ�ͷţ�����Ϊ������actor��ʧ���˺ڶ��ڲ�
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphereComponents;
	
	//��󣬺ڶ���������֣��ⲿ����Ϊһ����������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphereComponents;

	//U������Ϊ��actorӵ�еĺ�������������ͼ���ڰ�������
	//�ص��¼����ⲿactor���������ص�ʱ�������ⲿ��actor������Ϊ�ⲿ�����ʧ�ںڶ��ڲ�
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
