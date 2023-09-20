// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "ADFlak.generated.h"

UCLASS()
class AIRDEFENCE_API AADFlak : public APawn
{
	GENERATED_BODY()

public:
	AADFlak();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	float HorizontalDeflectionAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	float VerticalDeflectionAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	float MaxHorizontalAngularVelocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	float MaxVerticalAngularVelocity;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	int MaxFiringsPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	float RechargeTimePerProjectile;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Barrel")
	int MagazineSize;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
