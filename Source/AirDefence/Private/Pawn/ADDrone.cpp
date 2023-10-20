// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADDrone.h"

DEFINE_LOG_CATEGORY_STATIC(LogADDrone, All, All)

AADDrone::AADDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	DroneBoxStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	DroneBoxStaticMesh->SetupAttachment(Root);
	
	DroneSphereStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	DroneSphereStaticMesh->SetupAttachment(Root);
}

void AADDrone::BeginPlay()
{
	Super::BeginPlay();

	DroneBoxStaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	DroneSphereStaticMesh->SetRelativeLocation(FVector(0, 0, 10));
}

void AADDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

