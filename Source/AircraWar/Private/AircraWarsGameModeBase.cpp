// Fill out your copyright notice in the Description page of Project Settings.


#include "AircraWarsGameModeBase.h"


AAircraWarsGameModeBase::AAircraWarsGameModeBase()
{
	Score = 0;
	
}

void AAircraWarsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ShowHUD();
	GEngine->AddOnScreenDebugMessage(1,3,FColor::Red,TEXT("游戏开始！ "));
}

int AAircraWarsGameModeBase::GetScore()
{
	return Score;
}

void AAircraWarsGameModeBase::IncreaseScore()
{
	Score++;
	GEngine->AddOnScreenDebugMessage(1,3,FColor::Red, FString::FromInt(Score));
}
