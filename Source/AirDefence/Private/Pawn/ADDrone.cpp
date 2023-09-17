// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADDrone.h"

DEFINE_LOG_CATEGORY_STATIC(LogADDrone, All, All)

AADDrone::AADDrone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AADDrone::BeginPlay()
{
	Super::BeginPlay();
}

void AADDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

