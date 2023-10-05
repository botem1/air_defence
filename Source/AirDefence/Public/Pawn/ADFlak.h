// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "ADFlak.generated.h"

UCLASS()
class AIRDEFENCE_API AADFlak : public APawn
{
	GENERATED_BODY()

public:
	AADFlak();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* BarrelStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* FlakFoundationStaticMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput|InputContexts")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput|InputActions")
	UInputAction* IncreasePitchInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput|InputActions")
	UInputAction* DecreasePitchInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput|InputActions")
	UInputAction* IncreaseYawInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput|InputActions")
	UInputAction* DecreaseYawInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput|InputActions")
	UInputAction* IncreaseRollInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput|InputActions")
	UInputAction* DecreaseRollInputAction;

protected:
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
	UFUNCTION(BlueprintCallable)
	FRotator GetBarrelRotation();
	
	UFUNCTION(BlueprintCallable)
	void SetBarrelRotation(FRotator NewRotation);
	
	UFUNCTION(BlueprintCallable)
	float GetBarrelHorizontalDeflectionAngle();
	
	UFUNCTION(BlueprintCallable)
	void SetBarrelHorizontalDeflectionAngle(float NewHorizontalDeflectionAngle);
	
	UFUNCTION(BlueprintCallable)
	float GetBarrelVerticalDeflectionAngle();
	
	UFUNCTION(BlueprintCallable)
	void SetBarrelVerticalDeflectionAngle(float NewVerticalDeflectionAngle);
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	float DeltaDegree;
private:
	void IncreasePitch();
	void DecreasePitch();
	
	void IncreaseYaw();
	void DecreaseYaw();
	
	void IncreaseRoll();
	void DecreaseRoll();
};