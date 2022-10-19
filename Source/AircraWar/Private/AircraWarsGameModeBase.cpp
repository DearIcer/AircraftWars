// Fill out your copyright notice in the Description page of Project Settings.


#include "AircraWarsGameModeBase.h"
//#include "imgui.h"

AAircraWarsGameModeBase::AAircraWarsGameModeBase()
{
	Score = 0;
	ShowConsole = false;
}

void AAircraWarsGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AAircraWarsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ShowConsole = false;
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

void AAircraWarsGameModeBase::ShowImGuiWindows()
{

	//这里原本我封装了控制台，现在排Bug砍掉了==
	
}
