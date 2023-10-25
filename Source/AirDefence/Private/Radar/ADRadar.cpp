// Fill out your copyright notice in the Description page of Project Settings.


#include "Radar/ADRadar.h"

#include "Kismet/GameplayStatics.h"

#include "AirDefence/Public/Pawn/ADDrone.h"

AADRadar::AADRadar()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

AADDrone* AADRadar::GetCurrentDroneWithinRadius(FVector Location, float Radius)
{
	return (
		FVector::Dist(Location, CurrentDrone->GetActorLocation()) <= Radius
		? CurrentDrone
		: nullptr
	);
}

FVector AADRadar::GetCurrentDroneLastTickLocation()
{
	return CurrentDrone->GetActorLocation();
}

void AADRadar::Initialize(AADDrone* InDrone)
{
	CurrentDrone = InDrone;
}

void AADRadar::BeginPlay()
{
	Super::BeginPlay();
}

void AADRadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LastDroneLocation = CurrentDrone->GetActorLocation();
}

