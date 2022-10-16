// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"
class AEnemy;
UCLASS()
class AIRCRAWAR_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	UPROPERTY(EditAnywhere, Category = "MinimumDistanceToPlayer")
	float MinimumDistanceToPlayer;
	//声明玩家
	class ASpaceShip* SpaceShip;

	//定时器句柄
	FTimerHandle TimerHandle_Spawn;

	//敌人的生成间隔
	UPROPERTY(EditAnywhere, Category = "SpawnInterval")
	float SpawnInterval;

	//敌人最大生成数量
	UPROPERTY(EditAnywhere, Category = "maxEnemynum")
	int MaxEnemynum;
	//场上最大敌人数量
	UPROPERTY(EditAnywhere, Category = "maxEnemynum")
	int Thenumberofenemiesonthefield;

	UPROPERTY(EditAnywhere, Category = "maxEnemynum")
	int CurrentEnemyCount;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<AEnemy> Enemy;

	//生成区域
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* SpawnArea;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//找到玩家位置
	FVector GetGenerateLocation();

	//生成敌人
	void SpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DecreaseEnemyCount();

};
