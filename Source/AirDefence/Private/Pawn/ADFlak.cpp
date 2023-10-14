// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADFlak.h"

DEFINE_LOG_CATEGORY_STATIC(LogADFlak, All, All);

AADFlak::AADFlak()
{
	PrimaryActorTick.bCanEverTick = true;

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

FRotator AADFlak::GetBarrelRotation()
{
	return BarrelStaticMesh->GetRelativeRotation();
}

void AADFlak::SetBarrelRotation(FRotator NewRotation)
{
	if(NewRotation.Roll > 90)
	{
		NewRotation.Roll = 90;
	}
	
	if(NewRotation.Roll < -90)
	{
		NewRotation.Roll = -90;
	}
	
	NewRotation.Pitch = 0;
	
	BarrelStaticMesh->SetRelativeRotation(NewRotation);
}

float AADFlak::GetBarrelHorizontalDeflectionAngle()
{
	return GetBarrelRotation().Yaw;
}

void AADFlak::SetBarrelHorizontalDeflectionAngle(float NewHorizontalDeflectionAngle)
{
	FRotator NewBarrelRotation = BarrelStaticMesh->GetRelativeRotation();
	NewBarrelRotation.Yaw = NewHorizontalDeflectionAngle;

	SetBarrelRotation(NewBarrelRotation);
}

float AADFlak::GetBarrelVerticalDeflectionAngle()
{
	return GetBarrelRotation().Roll;
}

void AADFlak::SetBarrelVerticalDeflectionAngle(float NewVerticalDeflectionAngle)
{
	FRotator NewBarrelRotation = BarrelStaticMesh->GetRelativeRotation();
	NewBarrelRotation.Roll = NewVerticalDeflectionAngle;

	SetBarrelRotation(NewBarrelRotation);
}

void AADFlak::BeginPlay()
{
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::BeginPlay - log"));
	Super::BeginPlay();
	
	FlakFoundationStaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	BarrelStaticMesh->SetRelativeLocation(FVector(0, 0, 100));
}

void AADFlak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADFlak::IncreasePitch()
{
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::BeginPlay - log"));
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