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

private:
	UPROPERTY(EditDefaultsOnly, Category="Barrel")
	float HorizontalDeflectionAngle;

	UPROPERTY(EditDefaultsOnly, Category="Barrel")
	float VerticalDeflectionAngle;

	UPROPERTY(EditDefaultsOnly, Category="Barrel")
	float MaxHorizontalAngularVelocity;

	UPROPERTY(EditDefaultsOnly, Category="Barrel")
	float MaxVerticalAngularVelocity;

	UPROPERTY(EditDefaultsOnly, Category="Barrel")
	int MagazineSize;
	
	UPROPERTY(EditDefaultsOnly, Category="Barrel")
	int MaxFiringsPerSecond;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
