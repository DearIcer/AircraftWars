// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include"Engine/World.h"
#include "Components/BoxComponent.h"
#include"Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShip.h"
#include"Enemy.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	//设置根组件
	RootComponent = SpawnArea;

	//获取玩家

	//安全距离初值
	MinimumDistanceToPlayer = 1200.0f;

	SpawnInterval = 5.0f;

	//最大敌人数量
	MaxEnemynum = 30;

	//当前敌人数量
	CurrentEnemyCount = 0;

	//场上最大敌人数量
	Thenumberofenemiesonthefield = 10;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	//设置定时器调用生成敌人
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true, 0.0f);
}

FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance = 0.0f;
	FVector Location;
	while (Distance < MinimumDistanceToPlayer)
	{
		//在盒子内找到一个随机生成点
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);
		//获得与角色的距离
		Distance = (Location - SpaceShip->GetActorLocation()).Size();
	}
	return Location;
}

void AEnemySpawner::SpawnEnemy()
{
	if (SpaceShip->GetBDeath() == false && CurrentEnemyCount <= Thenumberofenemiesonthefield)
	{
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<AEnemy>(Enemy, GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *FString::SanitizeFloat(CurrentEnemyCount));
		CurrentEnemyCount++;
		//UE_LOG(LogTemp, Error, TEXT("%s"), *FString::SanitizeFloat(CurrentEnemyCount));
	}
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::DecreaseEnemyCount()
{
	if (CurrentEnemyCount > 0)
	{
		CurrentEnemyCount--;
		//UE_LOG(LogTemp, Error, TEXT("%s"), *FString::SanitizeFloat(CurrentEnemyCount));
	}
}

int AEnemySpawner::GetEnemyCount()
{
	return CurrentEnemyCount;
}


