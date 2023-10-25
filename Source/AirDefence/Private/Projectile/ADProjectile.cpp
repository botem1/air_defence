// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/ADProjectile.h"

#include "PhysicsEngine/PhysicsSettings.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "AirDefence/Public/Pawn/ADDrone.h"


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

void AADProjectile::Initialize(FVector InitialDirection, float InitialSpeed, AActor* InTarget)
{
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	
	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * InitialDirection;

	if(IsValid(InTarget) && IsValid(InTarget->GetRootComponent()))
	{
		DroneToReach = Cast<AADDrone>(InTarget);
		
		ProjectileMovementComponent->bIsHomingProjectile = true;
		ProjectileMovementComponent->HomingTargetComponent = InTarget->GetRootComponent();
		ProjectileMovementComponent->HomingAccelerationMagnitude = 500;
	}
}

void AADProjectile::BeginPlay()
{
	Super::BeginPlay();


}

void AADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::Tick - called."));
	// UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::Tick - ProjectileLocation: %s."), *GetActorLocation().ToString());
	// UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::Tick - DroneLocation: %s."), *DroneToReach->GetActorLocation().ToString());
	//
	if(IsValid(DroneToReach) && FVector::Dist(GetActorLocation(), DroneToReach->GetActorLocation()) < 300)
	{
		UE_LOG(LogADProjectile, Display, TEXT("AADProjectile::Tick - exploded."));

		const FVector ExplosionLocation = DroneToReach->GetActorLocation();
		
		if(IsValid(NiagaraSystemExplosion))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystemExplosion, ExplosionLocation);
		}

		if(IsValid(SoundExplosion))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundExplosion, ExplosionLocation, FRotator::ZeroRotator);
		}

		GetWorld()->DestroyActor(DroneToReach);
		GetWorld()->DestroyActor(this);
	}
}
