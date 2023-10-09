// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"

#include "InputMappingContext.h"
#include "InputAction.h"

#include "ADPlayerController.generated.h"

UCLASS()
class AIRDEFENCE_API AADPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	UPROPERTY()
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY()
	UInputAction* IncreasePitchInputAction;
};
