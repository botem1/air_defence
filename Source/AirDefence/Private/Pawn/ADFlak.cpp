// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/ADFlak.h"

#include "MovieSceneSequenceID.h"
#include "SNegativeActionButton.h"
#include "ToolContextInterfaces.h"

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

	DeltaDegree = 10;
}

FRotator AADFlak::GetBarrelRotation()
{
	return BarrelStaticMesh->GetRelativeRotation();
}

void AADFlak::SetBarrelRotation(FRotator NewRotation)
{
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::SetBarrelRotation - NewRotation: Pitch - %f, Yaw - %f, Roll - %f") ,NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	
	if(NewRotation.Roll > 90)
	{
		UE_LOG(LogADFlak, Warning, TEXT("AADFlak::SetBarrelRotation - new roll is > 90."));
		NewRotation.Roll = 90;
	}
	
	if(NewRotation.Roll < -90)
	{
		UE_LOG(LogADFlak, Warning, TEXT("AADFlak::SetBarrelRotation - new roll is < -90."));
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
	UE_LOG(LogADFlak, Warning, TEXT("ADFlak::IncreasePitch - entering."));
	
	FRotator NewRotation = GetBarrelRotation();
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::IncreasePitch - old rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	NewRotation.Pitch += DeltaDegree;
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::IncreasePitch - new rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);

	SetBarrelRotation(NewRotation);
	//BarrelStaticMesh->AddRelativeRotation(FRotator(DeltaDegree, 0, 0));
}

void AADFlak::DecreasePitch()
{
	FRotator NewRotation = GetBarrelRotation();
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::DecreasePitch - old rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	NewRotation.Pitch -= DeltaDegree;
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::DecreasePitch - new rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);

	SetBarrelRotation(NewRotation);
}

void AADFlak::IncreaseYaw()
{
	FRotator NewRotation = GetBarrelRotation();
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::IncreaseYaw - old rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	NewRotation.Yaw += DeltaDegree;
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::IncreaseYaw - new rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);

	SetBarrelRotation(NewRotation);
	//BarrelStaticMesh->AddRelativeRotation(FRotator(0, DeltaDegree, 0));
}

void AADFlak::DecreaseYaw()
{
	FRotator NewRotation = GetBarrelRotation();
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::DecreaseYaw - old rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	NewRotation.Yaw -= DeltaDegree;
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::DecreaseYaw - new rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);

	SetBarrelRotation(NewRotation);
}

void AADFlak::IncreaseRoll()
{
	FRotator NewRotation = GetBarrelRotation();
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::IncreaseRoll - old rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	NewRotation.Roll += DeltaDegree;
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::IncreaseRoll - new rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);

	SetBarrelRotation(NewRotation);
	//BarrelStaticMesh->AddRelativeRotation(FRotator(0, 0, DeltaDegree));
}

void AADFlak::DecreaseRoll()
{
	FRotator NewRotation = GetBarrelRotation();
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::DecreaseRoll - old rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
	NewRotation.Roll -= DeltaDegree;
	UE_LOG(LogADFlak, Warning, TEXT("AADFlak::DecreaseRoll - new rotation: Pitch - %f, Yaw - %f, Roll - %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);

	SetBarrelRotation(NewRotation);
}