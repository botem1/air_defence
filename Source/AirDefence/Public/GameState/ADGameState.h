// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"

#include "ADGameState.generated.h"

class AADDrone;
class AADFlak;
class AADRadar;

UCLASS()
class AIRDEFENCE_API AADGameState : public AGameState
{
	GENERATED_BODY()

public:
	AADGameState();

protected:
	AADDrone* SpawnDrone(FVector InBeginLocation, FVector InEndLocation, float InInitialSpeed, float InAccelerationMagnitude);
	
	AADFlak* SpawnFlak(FVector InitialLocation, FRotator InitialRotation, AADRadar* InRadar, float ProjectileBeginSpeed);

	AADRadar* SpawnRadar(FVector InitialLocation, const TArray<AADDrone*>& Drones);
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DroneToSpawnClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> FlakToSpawnClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> RadarToSpawnClass;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FRotator GetDefaultRotation();
};
