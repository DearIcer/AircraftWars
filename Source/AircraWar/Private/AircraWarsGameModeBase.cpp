// Fill out your copyright notice in the Description page of Project Settings.


#include "AircraWarsGameModeBase.h"


AAircraWarsGameModeBase::AAircraWarsGameModeBase()
{
	Score = 0;
	
}

void AAircraWarsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(1,3,FColor::Red,TEXT("游戏开始！ "));
}

void AAircraWarsGameModeBase::IncreaseScore()
{
	Score++;
	GEngine->AddOnScreenDebugMessage(1,3,FColor::Red, FString::FromInt(Score));
}
