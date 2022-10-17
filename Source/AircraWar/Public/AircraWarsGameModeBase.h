// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AircraWarsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AIRCRAWAR_API AAircraWarsGameModeBase : public AGameModeBase
{
	AAircraWarsGameModeBase();
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int Score;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHUD();
public:
	UFUNCTION(BlueprintCallable)
	int GetScore();
	
	void IncreaseScore();
};
