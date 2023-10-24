// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADDrone.h"

#include "Kismet/GameplayStatics.h"

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

void AADDrone::Initialize(FVector InBeginLocation, FVector InEndLocation, FVector InInitialDirection, float InInitialSpeed, float InAccelerationMagnitude)
{
	BeginLocation = InBeginLocation;
	EndLocation = InEndLocation;
	InitialSpeed = InInitialSpeed;
	AccelerationMagnitude = InAccelerationMagnitude;
	
	Velocity = InInitialDirection * InitialSpeed;

	Acceleration = InInitialDirection * AccelerationMagnitude;
}

void AADDrone::BeginPlay()
{
	Super::BeginPlay();
}

void AADDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(FVector::Dist(GetActorLocation(), EndLocation) > 200)
	{
		UpdateLocation(DeltaTime);
	}
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
