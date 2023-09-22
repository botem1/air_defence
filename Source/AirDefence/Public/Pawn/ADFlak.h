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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float HorizontalDeflectionAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float VerticalDeflectionAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float MaxHorizontalAngularVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float MaxVerticalAngularVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	int MaxFiringsPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float RechargeTimePerProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	int MagazineSize;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
