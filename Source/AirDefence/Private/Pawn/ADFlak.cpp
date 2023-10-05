// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADFlak.h"

#include "ToolContextInterfaces.h"

DEFINE_LOG_CATEGORY_STATIC(LogADFlak, All, All);

AADFlak::AADFlak()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
	
	BarrelStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	BarrelStaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	FlakFoundationStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlakFoundation"));
	FlakFoundationStaticMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	DeltaDegree = 10;
}

void AADFlak::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(IncreasePitchInputAction, ETriggerEvent::Triggered, this, &AADFlak::IncreasePitch);
	Input->BindAction(DecreasePitchInputAction, ETriggerEvent::Triggered, this, &AADFlak::DecreasePitch);
	
	Input->BindAction(IncreaseYawInputAction, ETriggerEvent::Triggered, this, &AADFlak::IncreaseYaw);
	Input->BindAction(DecreaseYawInputAction, ETriggerEvent::Triggered, this, &AADFlak::DecreaseYaw);
	
	Input->BindAction(IncreaseRollInputAction, ETriggerEvent::Triggered, this, &AADFlak::IncreaseRoll);
	Input->BindAction(DecreaseRollInputAction, ETriggerEvent::Triggered, this, &AADFlak::DecreaseRoll);
	
}

FRotator AADFlak::GetBarrelRotation()
{
	return BarrelStaticMesh->GetRelativeRotation();
}

void AADFlak::SetBarrelRotation(FRotator NewRotation)
{
	if(NewRotation.Pitch > 90)
	{
		NewRotation.Pitch = 90;
	}
	
	if(NewRotation.Pitch < -90)
	{
		NewRotation.Pitch = -90;
	}
	
	NewRotation.Roll = 0;

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
	return GetBarrelRotation().Pitch;
}

void AADFlak::SetBarrelVerticalDeflectionAngle(float NewVerticalDeflectionAngle)
{
	FRotator NewBarrelRotation = BarrelStaticMesh->GetRelativeRotation();
	NewBarrelRotation.Pitch = NewVerticalDeflectionAngle;

	SetBarrelRotation(NewBarrelRotation);
}

void AADFlak::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	FlakFoundationStaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	BarrelStaticMesh->SetRelativeLocation(FVector(0, 0, 100));

	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::BeginPlay() - testing"));
}

void AADFlak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AADFlak::IncreasePitch()
{
	UE_LOG(LogADFlak, Warning, TEXT("ADFlak::IncreasePitch - trigerring event."));
	
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