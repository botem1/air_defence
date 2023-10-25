// Fill out your copyright notice in the Description page of Project Settings.


#include "ADDefaultPawn/MyDefaultPawn.h"

#include "AirDefence/Public/Pawn/ADFlak.h"

DEFINE_LOG_CATEGORY_STATIC(LogADMyDefaultPawn, All, All);

AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyDefaultPawn::Initialize(AADFlak* InFlak)
{
	Flak = InFlak;
}

void AMyDefaultPawn::Fire()
{
	UE_LOG(LogADMyDefaultPawn, Warning, TEXT("AMyDefaultPawn::Fire - fired."));
	if(IsValid(Flak))
	{
		Flak->FireProjectile();
	} else
	{
		UE_LOG(LogADMyDefaultPawn, Warning, TEXT("AMyDefaultPawn::Fire - flak is not valid"));
	}
}

void AMyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
