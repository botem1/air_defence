// Fill out your copyright notice in the Description page of Project Settings.

#include "GameState/ADGameState.h"

DEFINE_LOG_CATEGORY_STATIC(LogADGameState, All, All)

AADGameState::AADGameState()
{
}

void AADGameState::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogADGameState, Warning, TEXT("AADGameState::BeginPlay - called."));
}

void AADGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
