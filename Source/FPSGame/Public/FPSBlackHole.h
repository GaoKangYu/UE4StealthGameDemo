// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

//新增黑洞类
//目的：理清cpp与引擎的协同逻辑，尝试实现部分功能

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
//黑洞是一个有实体可视的对象，因此是继承于actor的
class FPSGAME_API AFPSBlackHole : public AActor
{
	//简单理解为宏定义注册对象
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//构造函数
	AFPSBlackHole();

protected:
	//所以有的组件都需要公布给蓝图编辑
	// 最基本的显示这个actor
	//为了显示这个actor需要进行两个操作，首先是定义静态网格体，用于承载这个actor
	//U所有物，宏，公布给蓝图，权限为可见但不可编辑
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//随后，黑洞由球体表现，内部球体实现资源释放，表现为其他的actor消失在了黑洞内部
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphereComponents;
	
	//随后，黑洞由球体表现，外部球体为一般美术表现
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphereComponents;

	//U函数，为本actor拥有的函数，公布给蓝图用于绑定与链接
	//重叠事件，外部actor与内球体重叠时，销毁外部的actor，表现为外部组件消失在黑洞内部
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
