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
	//ProjectileMovementComponent->bRotationFollowsVelocity = true;
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
	UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::Initialize - called."));
	
	FRotator ProjectileRotation = GetProjectileRotation();
	UE_LOG(LogADProjectile, Display, TEXT("AADProjectile::Initialize - ProjectileRotation(Pitch: %f; Roll: %f; Yaw: %f)."), ProjectileRotation.Pitch, ProjectileRotation.Roll, ProjectileRotation.Yaw);
	
	float Roll = ProjectileRotation.Roll;
	float Yaw = ProjectileRotation.Yaw;

	float VelocityProjectionXY = VelocityMagnitude * FMath::Sin(FMath::DegreesToRadians(Roll));

	float dx = VelocityProjectionXY * FMath::Sin(FMath::DegreesToRadians(Yaw));
	float dy = VelocityProjectionXY * FMath::Cos(FMath::DegreesToRadians(Yaw));
	float dz = VelocityMagnitude * FMath::Cos(FMath::DegreesToRadians(Roll));
	
	FVector VelocityVector(-dx, dy, dz);
	//UE_LOG(LogADProjectile, Display, TEXT("AADProjectile::Initialize - VelocityVector.Rotation()(Pitch: %f; Roll: %f; Yaw: %f)."), VelocityVector.Rotation().Pitch, VelocityVector.Rotation().Roll, VelocityVector.Rotation().Yaw);

	FVector VelocityBegin = GetProjectileLocation();
	//UE_LOG(LogADFlak, Display, TEXT("AADProjectile::Initialize - VelocityBegin(X: %f; Y: %f; Z: %f)."), VelocityBegin.X, VelocityBegin.Y, VelocityBegin.Z);
	
	DrawDebugLine(GetWorld(), GetProjectileLocation(), GetProjectileLocation() + VelocityVector, FColor::Red, true, -1, 0, 3);

	SetProjectileVelocity(VelocityVector);
}

void AADProjectile::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::BeginPlay - called."));

	ProjectileMovementComponent->Activate();
}

void AADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogADProjectile, Warning, TEXT("AADProjectile::Tick - called."))

	UE_LOG(LogADProjectile, Display, TEXT("AADProjectile::Tick - Velocity Rotation(Pitch: %f; Roll: %f; Yaw: %f)."), GetProjectileVelocity().Rotation().Pitch, GetProjectileVelocity().Rotation().Roll, GetProjectileVelocity().Rotation().Yaw);
	UE_LOG(LogADProjectile, Display, TEXT("AADProjectile::Tick - Projectile Mesh Rotation(Pitch: %f; Roll: %f; Yaw: %f)."), GetProjectileRotation().Pitch, GetProjectileRotation().Roll, GetProjectileRotation().Yaw);
	
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