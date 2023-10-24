// Fill out your copyright notice in the Description page of Project Settings.


#include "Radar/ADRadar.h"

#include "Kismet/GameplayStatics.h"

#include "AirDefence/Public/Pawn/ADDrone.h"

AADRadar::AADRadar()
{
	PrimaryActorTick.bCanEverTick = true;
}

AADDrone* AADRadar::GetCurrentDroneWithinRadius(FVector Location, float Radius)
{
	return (
		FVector::Dist(Location, Drones[0]->GetActorLocation()) <= Radius
		? Drones[0]
		: nullptr
	);
}

void AADRadar::Initialize(const TArray<AADDrone*>& InDrones)
{
	Drones = InDrones;
}

void AADRadar::BeginPlay()
{
	Super::BeginPlay();
	
}

void AADRadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

