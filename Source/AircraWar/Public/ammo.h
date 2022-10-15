// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ammo.generated.h"

UCLASS()
class AIRCRAWAR_API Aammo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aammo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")	
	class UStaticMeshComponent* Bullet;

	UPROPERTY(VisibleAnywhere, Category = "ProjectleMoveComponent")
	class UProjectileMovementComponent* ProjectleMoveComponent;

	UPROPERTY(VisibleAnywhere, Category = "FX")
	class UParticleSystemComponent* ParticleSystem;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
