// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADFlak.h"

#include "Kismet/GameplayStatics.h"
#include "Pawn/ADDrone.h"

DEFINE_LOG_CATEGORY_STATIC(LogADFlak, All, All);

AADFlak::AADFlak()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	BarrelStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	BarrelStaticMesh->SetupAttachment(Root);
	
	FlakFoundationStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlakFoundation"));
	FlakFoundationStaticMesh->SetupAttachment(Root);

	DeltaDegree = 10;
}

void AADFlak::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(IncreasePitchInputAction, ETriggerEvent::Started, this, &AADFlak::IncreasePitch);
	EnhancedInput->BindAction(DecreasePitchInputAction, ETriggerEvent::Started, this, &AADFlak::DecreasePitch);
	
	EnhancedInput->BindAction(IncreaseYawInputAction, ETriggerEvent::Started, this, &AADFlak::IncreaseYaw);
	EnhancedInput->BindAction(DecreaseYawInputAction, ETriggerEvent::Started, this, &AADFlak::DecreaseYaw);
	
	EnhancedInput->BindAction(IncreaseRollInputAction, ETriggerEvent::Started, this, &AADFlak::IncreaseRoll);
	EnhancedInput->BindAction(DecreaseRollInputAction, ETriggerEvent::Started, this, &AADFlak::DecreaseRoll);
}

void AADFlak::Initialize(float InProjectileBeginSpeed, AADRadar* InRadar)
{
	ProjectileBeginSpeed = InProjectileBeginSpeed;

	if(IsValid(InRadar))
	{
		Radar = InRadar;
	} else
	{
		Radar = nullptr;
	}
}

FRotator AADFlak::GetBarrelRotation()
{
	return BarrelStaticMesh->GetRelativeRotation();
}

void AADFlak::SetBarrelRotation(FRotator NewRotation)
{
	if(NewRotation.Pitch > 80)
	{
		NewRotation.Pitch = 80;
	}
	
	if(NewRotation.Pitch < -80)
	{
		NewRotation.Pitch = -80;
	}
	
	NewRotation.Roll = 0;
	
	BarrelStaticMesh->SetRelativeRotation(NewRotation);

}

FVector AADFlak::GetBarrelWorldLocation()
{
	return BarrelStaticMesh->GetComponentLocation();
}

float AADFlak::GetBarrelLength()
{
	return 240.0;
}

void AADFlak::BeginPlay()
{
	Super::BeginPlay();
}

void AADFlak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADFlak::FireProjectile()
{
	if(IsValid(Radar) && IsValid(Radar->GetCurrentDroneWithinRadius(GetActorLocation(), VisibilityRadius)))
	{
		AADDrone* Target = Radar->GetCurrentDroneWithinRadius(GetActorLocation(), VisibilityRadius);

		const FVector BarrelDirection = (Target->GetActorLocation() - GetBarrelWorldLocation()).GetSafeNormal();
		
		SetBarrelRotation(BarrelDirection.Rotation() + FRotator(-90, 0, 0));
		
		FTransform ProjectileSpawnTransform(GetBarrelRotation(), CalculateProjectileSpawnLocation());
	
		AADProjectile* SpawnedProjectile = GetWorld()->SpawnActorDeferred<AADProjectile>(
			ProjectileToSpawnClass,
			ProjectileSpawnTransform,
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
	
		if(IsValid(SpawnedProjectile))
		{
			const FVector InitialProjectileDirection = (CalculateProjectileSpawnLocation() - GetBarrelWorldLocation()).GetSafeNormal();
		
			SpawnedProjectile->Initialize(InitialProjectileDirection, ProjectileBeginSpeed, Target);
	
			UGameplayStatics::FinishSpawningActor(SpawnedProjectile, ProjectileSpawnTransform);
		}
	}

}

FVector AADFlak::GetDroneVelocityThisTick(FVector CurrentDroneLocation, float DeltaTime)
{
	return (CurrentDroneLocation - Radar->GetCurrentDroneLastTickLocation()) / DeltaTime;
}

FVector AADFlak::CalculateProjectileSpawnLocation()
{
	float Pitch = GetBarrelRotation().Pitch;
	float Yaw = GetBarrelRotation().Yaw;
	
	float BarrelProjectionXY = GetBarrelLength() * FMath::Sin(FMath::DegreesToRadians(Pitch));
	
	float dx = BarrelProjectionXY * FMath::Cos(FMath::DegreesToRadians(Yaw));
	float dy = BarrelProjectionXY * FMath::Sin(FMath::DegreesToRadians(Yaw));
	float dz = GetBarrelLength() * FMath::Cos(FMath::DegreesToRadians(Pitch));

	FVector CurrentBarrelWorldLocation = GetBarrelWorldLocation();

	FVector Location(
		CurrentBarrelWorldLocation.X - dx,
		CurrentBarrelWorldLocation.Y - dy,
		CurrentBarrelWorldLocation.Z + dz
	);

	return Location;
}

void AADFlak::IncreasePitch()
{
	FRotator NewRotation = GetBarrelRotation();
	NewRotation.Pitch += DeltaDegree;

	SetBarrelRotation(NewRotation);
}

void AADFlak::DecreasePitch()
{
	FRotator NewRotation = GetBarrelRotation();
	NewRotation.Pitch -= DeltaDegree;

	SetBarrelRotation(NewRotation);
}

void AADFlak::IncreaseYaw()
{
	FRotator NewRotation = GetBarrelRotation();
	NewRotation.Yaw += DeltaDegree;

	SetBarrelRotation(NewRotation);
}

void AADFlak::DecreaseYaw()
{
	FRotator NewRotation = GetBarrelRotation();
	NewRotation.Yaw -= DeltaDegree;

	SetBarrelRotation(NewRotation);
}

void AADFlak::IncreaseRoll()
{
	FRotator NewRotation = GetBarrelRotation();
	NewRotation.Roll += DeltaDegree;

	SetBarrelRotation(NewRotation);
}

void AADFlak::DecreaseRoll()
{
	FRotator NewRotation = GetBarrelRotation();
	NewRotation.Roll -= DeltaDegree;

	SetBarrelRotation(NewRotation);
}