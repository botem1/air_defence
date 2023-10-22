// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADDrone.h"

DEFINE_LOG_CATEGORY_STATIC(LogADDrone, All, All)

AADDrone::AADDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	PropellerLeftStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftProperller"));
	PropellerLeftStaticMesh->SetupAttachment(Root);
	
	PropellerRightStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightProperller"));
	PropellerRightStaticMesh->SetupAttachment(Root);
	
	BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	BodyStaticMesh->SetupAttachment(Root);
}

void AADDrone::Initialize(FVector SpawnDirection)
{
	Velocity = SpawnDirection * InitialSpeed;

	Acceleration = SpawnDirection * AccelerationMagnitude;

	BodyStaticMesh->SetRelativeRotation(SpawnDirection.Rotation());
	SetActorLocation(BeginLocation);
}

void AADDrone::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector DroneInitialDirection = (EndLocation - BeginLocation).GetSafeNormal();
	Initialize(DroneInitialDirection);
}

void AADDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADDrone::UpdateVelocity(float DeltaTime)
{
	Velocity += Acceleration * DeltaTime;
}

void AADDrone::UpdateLocation(float DeltaTime)
{
	UpdateVelocity(DeltaTime);

	const FVector NewLocation = Root->GetComponentLocation() + Velocity * DeltaTime;

	SetActorLocation(NewLocation);
}
