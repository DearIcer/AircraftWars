// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"
#include "SpaceShip.h"
#include "Kismet/GameplayStatics.h"
#include"Kismet/KismetMathLibrary.h"
#include "Misc/App.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include<particles/ParticleSystem.h>
#include "Bullet.h"
//#include"ammo.h"
#include"EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include<particles/ParticleSystemComponent.h>
#include"AircraWarsGameModeBase.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemySpeed = 500.0f;
	//实例化碰撞模型
	CollisionCom = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	//设置根组件
	RootComponent = CollisionCom;

	//实例化模型
	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	//绑定根组件
	ShipSM->SetupAttachment(RootComponent);
	//实例化子弹槽位
	SpawnPiont = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SpawnPiont->SetupAttachment(ShipSM);

	//开火初值
	Time_BetweenShot = 3.0f;
}

void AEnemy::MoveTowardsPlayer()
{
	if(SpaceShip->GetBDeath() != true)
	{
		//用玩家的位置减去角色位置等于朝向敌人的向量
		FVector Direction = (SpaceShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		//控制移动
		AddActorWorldOffset(Direction * EnemySpeed * FApp::GetDeltaTime(), true);
		//控制旋转
		//获得玩家旋转向量
		FVector TargetLocation = FVector(SpaceShip->GetActorLocation().X, SpaceShip->GetActorLocation().Y, SpaceShip->GetActorLocation().Z);
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation));
	}

}

void AEnemy::Fire()
{
	if(SpaceShip->GetBDeath() != true)
	{
		if (Bullet != nullptr)
		{
			FActorSpawnParameters SpawnParameters;
			FVector TargetLocation = FVector(SpaceShip->GetActorLocation().X, SpaceShip->GetActorLocation().Y, SpaceShip->GetActorLocation().Z);
			GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPiont->GetComponentLocation(), UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation), SpawnParameters);
			//GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::Blue, TEXT("EnemyFire"));
		}
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetColor();

	//获取游戏模式
	AWGameModeBase = Cast<AAircraWarsGameModeBase>(UGameplayStatics::GetGameMode(this));
	//获取玩家0号
	SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));//强转类型

	TArray<AActor*>EnemySpawnerArray;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), EnemySpawnerArray);
	EnemySpawner = Cast<AEnemySpawner>(EnemySpawnerArray[0]);
	
	//创建敌人开火定时器
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShot, this, &AEnemy::Fire, Time_BetweenShot, true, 0.0f);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SpaceShip)
	{
		//移动玩家
		MoveTowardsPlayer();
	}
}

void AEnemy::OnDeath()
{
	//GEngine->AddOnScreenDebugMessage(0,3,FColor::Red,TEXT("EnemyDeath"));
	//加分
	if(AWGameModeBase)
	{
		AWGameModeBase->IncreaseScore();
	}
	if(FX_Boom != nullptr)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShot);
		UGameplayStatics::SpawnEmitterAtLocation(this,FX_Boom,GetActorLocation(),FRotator::ZeroRotator);
		Destroy();
	}

}

