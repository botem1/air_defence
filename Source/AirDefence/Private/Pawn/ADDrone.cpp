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

void AADDrone::Initialize()
{
	const FVector InitialDirection = EndLocation - BeginLocation;
	
	Velocity = InitialDirection * InitialSpeed;

	Acceleration = InitialDirection * AccelerationMagnitude;

	BodyStaticMesh->SetRelativeRotation(InitialDirection.Rotation());

	BodyStaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	SetActorLocation(BeginLocation);

	UE_LOG(LogADDrone, Warning, TEXT("AADDrone::Initialize - actor location: %s"), *GetActorLocation().ToString());
}

void AADDrone::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void AADDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation(DeltaTime);
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
