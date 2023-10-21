// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/ADProjectile.h"

#include "PhysicsEngine/PhysicsSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogADProjectile, All, All)

AADProjectile::AADProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	ProjectileStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileStaticMeshComponent"));
	
	ProjectileStaticMeshComponent->SetupAttachment(RootComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void AADProjectile::Initialize(FVector SpawnDirection, AActor* InTarget)
{
	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * SpawnDirection;

	if (IsValid(InTarget) && IsValid(InTarget->GetRootComponent()))
	{
		ProjectileMovementComponent->HomingTargetComponent = InTarget->GetRootComponent();
	}
}