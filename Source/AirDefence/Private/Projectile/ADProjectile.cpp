// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/ADProjectile.h"

#include "PhysicsEngine/PhysicsSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogADProjectile, All, All)

AADProjectile::AADProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	ProjectileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	ProjectileStaticMesh->SetupAttachment(Root);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
}

FVector AADProjectile::GetProjectileLocation()
{
	return ProjectileStaticMesh->GetComponentLocation();
}

void AADProjectile::SetProjectileLocation(FVector NewLocation)
{
	ProjectileStaticMesh->SetWorldLocation(NewLocation);
}

FRotator AADProjectile::GetProjectileRotation()
{
	return ProjectileStaticMesh->GetComponentRotation();
}

void AADProjectile::SetProjectileRotation(FRotator NewRotation)
{
	ProjectileStaticMesh->SetRelativeRotation(NewRotation);
}

FVector AADProjectile::GetProjectileVelocity()
{
	return Velocity;
}

void AADProjectile::SetProjectileVelocity(FVector NewVelocity)
{
	Velocity = NewVelocity;
}

void AADProjectile::Initialize(float VelocityMagnitude)
{

	FRotator ProjectileRotation = GetProjectileRotation();

	float Roll = ProjectileRotation.Roll;
	float Yaw = ProjectileRotation.Yaw;

	float VelocityProjectionXY = VelocityMagnitude * FMath::Sin(FMath::DegreesToRadians(Roll));

	float dx = VelocityProjectionXY * FMath::Sin(FMath::DegreesToRadians(Yaw));
	float dy = VelocityProjectionXY * FMath::Cos(FMath::DegreesToRadians(Yaw));
	float dz = VelocityMagnitude * FMath::Cos(FMath::DegreesToRadians(Roll));
	
	FVector VelocityVector(-dx, dy, dz);

	DrawDebugLine(GetWorld(), GetProjectileLocation(), GetProjectileLocation() + VelocityVector, FColor::Red, true, -1, 0, 3);

	SetProjectileVelocity(VelocityVector);
}

void AADProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComponent->Activate();
}

void AADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector LocationChange = ProjectileMovementComponent->ComputeMoveDelta(GetProjectileVelocity(), DeltaTime);

	FVector CurrentLocation = GetProjectileLocation();
	FVector NewLocation(
		CurrentLocation.X + LocationChange.X,
		CurrentLocation.Y + LocationChange.Y,
		CurrentLocation.Z + LocationChange.Z
	);

	SetProjectileLocation(NewLocation);
	SetProjectileRotation(GetProjectileVelocity().Rotation());
	
	FVector CurrentVelocity = GetProjectileVelocity();
	DrawDebugLine(GetWorld(), GetProjectileLocation(), GetProjectileLocation() + CurrentVelocity, FColor::Green, true, -1, 0, 3);

	FVector NewVelocity = ProjectileMovementComponent->ComputeVelocity(CurrentVelocity, DeltaTime);

	SetProjectileVelocity(NewVelocity);
	ProjectileMovementComponent->SetVelocityInLocalSpace(NewVelocity);
}