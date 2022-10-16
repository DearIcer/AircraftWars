// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enemy.generated.h"
class AEnemyBullet;
class ABullet;
UCLASS()
class AIRCRAWAR_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	//朝着玩家移动
	void MoveTowardsPlayer();
	//敌人开火
	void Fire();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();
protected:
	//完全可见
	UPROPERTY(VisibleAnywhere, Category = "Component")
	//声明碰撞组件
	class USphereComponent* CollisionCom;

	//完全可见,蓝图可见
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	//声明网格组件
	UStaticMeshComponent* ShipSM;
	//声明玩家
	class ASpaceShip* SpaceShip;
	class AEnemySpawner* EnemySpawner;

	//完全可见
	//子弹槽位1
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPiont;
	
	//爆炸粒子
	UPROPERTY(EditAnywhere, Category = "FX")
	class UParticleSystem* FX_Boom;

	//变量声明
	UPROPERTY(EditAnywhere, Category = "Move")
	float EnemySpeed;

	//开火间隔
	UPROPERTY(EditAnywhere, Category = "Fire")
	float Time_BetweenShot;
	FTimerHandle TimerHandle_BetweenShot;

	//声明子弹
	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<ABullet> Bullet;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnDeath();
};
