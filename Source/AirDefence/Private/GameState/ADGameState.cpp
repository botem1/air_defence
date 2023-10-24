// Fill out your copyright notice in the Description page of Project Settings.

#include "GameState/ADGameState.h"

#include "AirDefence/Public/Pawn/ADDrone.h"
#include "AirDefence/Public/Pawn/ADFlak.h"
#include "AirDefence/Public/Radar/ADRadar.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogADGameState, All, All)

AADGameState::AADGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

AADDrone* AADGameState::SpawnDrone(FVector InBeginLocation, FVector InEndLocation, float InInitialSpeed, float InAccelerationMagnitude)
{
	
	const FVector InitialDirection = (InEndLocation - InBeginLocation).GetSafeNormal();
	
	FRotator DroneSpawnRotation(
		0,
		InitialDirection.Rotation().Yaw,
		0
	);

	FVector DroneSpawnLocation = InBeginLocation;
	
	AADDrone* SpawnedDrone = GetWorld()->SpawnActorDeferred<AADDrone>(
		DroneToSpawnClass,
		FTransform(DroneSpawnRotation, DroneSpawnLocation),
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	
	if(IsValid(SpawnedDrone))
	{
		SpawnedDrone->Initialize(InBeginLocation, InEndLocation, InitialDirection, InInitialSpeed, InAccelerationMagnitude);
	
		UGameplayStatics::FinishSpawningActor(SpawnedDrone, FTransform(DroneSpawnRotation, DroneSpawnLocation));
	}

	return SpawnedDrone;
}

AADFlak* AADGameState::SpawnFlak(FVector InitialLocation, FRotator InitialRotation, AADRadar* InRadar, float InProjectileBeginSpeed)
{
	AADFlak* SpawnedFlak = GetWorld()->SpawnActorDeferred<AADFlak>(
		FlakToSpawnClass,
		FTransform(InitialRotation, InitialLocation),
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if(IsValid(SpawnedFlak))
	{
		SpawnedFlak->Initialize(InProjectileBeginSpeed, InRadar);

		UGameplayStatics::FinishSpawningActor(SpawnedFlak, FTransform(InitialRotation, InitialLocation));
	}

	return SpawnedFlak;
}

AADRadar* AADGameState::SpawnRadar(FVector InitialLocation, const TArray<AADDrone*>& Drones)
{
		AADRadar* SpawnedRadar = GetWorld()->SpawnActorDeferred<AADRadar>(
		RadarToSpawnClass,
		FTransform(GetDefaultRotation(), InitialLocation),
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if(IsValid(SpawnedRadar))
	{
		SpawnedRadar->Initialize(Drones);

		UGameplayStatics::FinishSpawningActor(SpawnedRadar, FTransform(GetDefaultRotation(), InitialLocation));
	}

	return SpawnedRadar;
}

void AADGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AADGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FRotator AADGameState::GetDefaultRotation()
{
	return FRotator(0, 0, 0);
}
