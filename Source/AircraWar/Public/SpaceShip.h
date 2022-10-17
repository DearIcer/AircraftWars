// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"
class ABullet;
UCLASS()
class AIRCRAWAR_API ASpaceShip : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* CollisionCom;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCameraComponent* CameraComp;

	//子弹槽位1
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPiont;
	
	//子弹槽位2
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPiont2;
	
	//获取玩家控制器
	APlayerController* PC;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<ABullet> Bullet;
	
	//粒子组件
	UPROPERTY(VisibleAnywhere, Category = "FX")
	class UParticleSystemComponent* ParticleSystem;

	//爆炸粒子
	UPROPERTY(EditAnywhere, Category = "FX")
	class UParticleSystem* FX_Boom;

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

	//角色移动速度
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, Category = "Fire")
	float Time_BetweenShot;
protected:
	bool IsUpMove;
	bool IsRightMove;
	bool IsDead;
	
	//这里丢定时器
	FTimerHandle TimerHandle_BetweenShot;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//角色指向鼠标
	void LookAtCursor();

	//设置向上移动
	void MoveUp(float Value);

	//设置向右移动
	void MoveRight(float Value);

	//移动主函数
	void Move();
	
	//开火
	void Fire();

	void StarFire();

	void EndFire();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnDeath();

	//提供接口给外接知道玩家是否死亡
	FORCEINLINE bool GetBDeath()
	{
		return IsDead;
	}
};
