// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"

#include "ADGameState.generated.h"

UCLASS()
class AIRDEFENCE_API AADGameState : public AGameState
{
	GENERATED_BODY()

public:
	AADGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
