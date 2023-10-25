// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "MyDefaultPawn.generated.h"

class AADFlak;

UCLASS()
class AIRDEFENCE_API AMyDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	AMyDefaultPawn();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Initialize(AADFlak* InFlak);

protected:
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	AADFlak* Flak;
};
