// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "ADDrone.generated.h"

UCLASS()
class AIRDEFENCE_API AADDrone : public APawn
{
	GENERATED_BODY()

public:
	AADDrone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
