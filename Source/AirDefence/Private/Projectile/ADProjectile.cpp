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
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
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
	return ProjectileStaticMesh->GetRelativeRotation();
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

void AADProjectile::Initialize(FVector InitialDirection)
{
	UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::Initialize - called."));
	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * InitialDirection;
	DrawDebugLine(GetWorld(), GetProjectileLocation(), GetProjectileLocation() + ProjectileMovementComponent->Velocity, FColor::Purple, true, -1, 0, 3);
}

void AADProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugLine(
		GetWorld(),
		GetProjectileLocation(),
		GetProjectileLocation() + ProjectileMovementComponent->Velocity,
		FColor::Red,
		true,
		-1,
		0,
		3
	);
}