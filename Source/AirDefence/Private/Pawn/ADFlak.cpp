// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADFlak.h"

DEFINE_LOG_CATEGORY_STATIC(LogADFlak, All, All);

AADFlak::AADFlak()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
	
	BarrelStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"))
	BarrelStaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	FlakFoundationStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlakFoundation"));
	FlakFoundationStaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
}

void AADFlak::BeginPlay()
{
	Super::BeginPlay();
}

void AADFlak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADFlak::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
