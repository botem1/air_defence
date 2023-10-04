// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADFlak.h"

#include "ToolContextInterfaces.h"

DEFINE_LOG_CATEGORY_STATIC(LogADFlak, All, All);

AADFlak::AADFlak()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
	
	BarrelStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	BarrelStaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	FlakFoundationStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlakFoundation"));
	FlakFoundationStaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AADFlak::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FRotator AADFlak::GetBarrelRotation()
{
	return BarrelStaticMesh->GetRelativeRotation();
}

void AADFlak::SetBarrelRotation(FRotator NewRotation)
{
	if(NewRotation.Pitch > 90)
	{
		NewRotation.Pitch = 90;
	}
	
	if(NewRotation.Pitch < -90)
	{
		NewRotation.Pitch = -90;
	}
	
	NewRotation.Roll = 0;

	BarrelStaticMesh->SetRelativeRotation(NewRotation);
}

float AADFlak::GetBarrelHorizontalDeflectionAngle()
{
	return GetBarrelRotation().Yaw;
}

void AADFlak::SetBarrelHorizontalDeflectionAngle(float NewHorizontalDeflectionAngle)
{
	FRotator NewBarrelRotation = BarrelStaticMesh->GetRelativeRotation();
	NewBarrelRotation.Yaw = NewHorizontalDeflectionAngle;

	SetBarrelRotation(NewBarrelRotation);
}

float AADFlak::GetBarrelVerticalDeflectionAngle()
{
	return GetBarrelRotation().Pitch;
}

void AADFlak::SetBarrelVerticalDeflectionAngle(float NewVerticalDeflectionAngle)
{
	FRotator NewBarrelRotation = BarrelStaticMesh->GetRelativeRotation();
	NewBarrelRotation.Pitch = NewVerticalDeflectionAngle;

	SetBarrelRotation(NewBarrelRotation);
}

void AADFlak::BeginPlay()
{
	Super::BeginPlay();
	
	FlakFoundationStaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	BarrelStaticMesh->SetRelativeLocation(FVector(0, 0, 100));
}

void AADFlak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

