// Fill out your copyright notice in the Description page of Project Settings.

#include "GameState/ADGameState.h"

#include "ADDefaultPawn/MyDefaultPawn.h"
#include "AirDefence/Public/Pawn/ADDrone.h"
#include "AirDefence/Public/Pawn/ADFlak.h"
#include "AirDefence/Public/Radar/ADRadar.h"
#include "AirDefence/Public/ADDefaultPawn/MyDefaultPawn.h"

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

AADRadar* AADGameState::SpawnRadar(FVector InitialLocation, AADDrone* Drone)
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
		SpawnedRadar->Initialize(Drone);

		UGameplayStatics::FinishSpawningActor(SpawnedRadar, FTransform(GetDefaultRotation(), InitialLocation));
	}

	return SpawnedRadar;
}

AMyDefaultPawn* AADGameState::SpawnDefaultPawn(FVector InitialLocation, AADFlak* InFlak)
{
	AMyDefaultPawn* SpawnedDefaultPawn = GetWorld()->SpawnActorDeferred<AMyDefaultPawn>(
		DefaultPawnToSpawnClass,
		FTransform(GetDefaultRotation(), InitialLocation),
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if(IsValid(SpawnedDefaultPawn))
	{
		SpawnedDefaultPawn->Initialize(InFlak);

		UGameplayStatics::FinishSpawningActor(SpawnedDefaultPawn, FTransform(GetDefaultRotation(), InitialLocation));
	}

	return SpawnedDefaultPawn;
}

void AADGameState::BeginPlay()
{
	Super::BeginPlay();
	
	FVector DroneBeginLocation(3000, 3000, 2000);
	FVector DroneEndLocation(-2000, -2000, 2000);
	
	AADDrone* Drone = SpawnDrone(DroneBeginLocation, DroneEndLocation, 700, 30);
	
	AADRadar* Radar = SpawnRadar(GetDefaultLocation(), Drone);

	AADFlak* Flak = SpawnFlak(FVector::ZeroVector, FRotator::ZeroRotator, Radar, 7000);

	AMyDefaultPawn* DefaultPawn = SpawnDefaultPawn(FVector(1000, 1000, 1000), Flak);
	GetWorld()->GetFirstPlayerController()->Possess(DefaultPawn);
}

void AADGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FRotator AADGameState::GetDefaultRotation()
{
	return FRotator(0, 0, 0);
}

FVector AADGameState::GetDefaultLocation()
{
	return FVector(0, 0, 0);
}