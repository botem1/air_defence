// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "Math/Vector.h"

#include "ADDrone.generated.h"

UCLASS()
class AIRDEFENCE_API AADDrone : public APawn
{
	GENERATED_BODY()

public:
	AADDrone();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector DestinationCoordinates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Parameters")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Parameters")
	FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Parameters")
	FVector Jerk;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
