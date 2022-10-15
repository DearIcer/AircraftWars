// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include<particles/ParticleSystemComponent.h>
#include<GameFramework/ProjectileMovementComponent.h>
#include<Kismet/GameplayStatics.h>
// Sets default values
ABullet::ABullet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;
	//实例化子弹模型
	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Bullet->SetupAttachment(RootComponent);

	//实例化抛物线组件 UProjectileMovementComponent
	ProjectleMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectleMoveComponent"));
	ProjectleMoveComponent->InitialSpeed = 5000.0f;
	//实例化粒子系统
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


