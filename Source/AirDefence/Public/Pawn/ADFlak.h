// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerController/ADPlayerController.h"

#include "AirDefence/Public/Projectile/ADProjectile.h"

#include "ADFlak.generated.h"

UCLASS()
class AIRDEFENCE_API AADFlak : public APawn
{
	GENERATED_BODY()

public:
	AADFlak();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
	FRotator GetBarrelRotation();
	
	UFUNCTION(BlueprintCallable)
	void SetBarrelRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable)
	FVector GetBarrelWorldLocation();

	UFUNCTION(BlueprintCallable)
	float GetBarrelLength();

protected:
	UFUNCTION(BlueprintCallable)
	AADProjectile* SpawnProjectile(FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* BarrelStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* FlakFoundationStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AADProjectile> ProjectileToSpawnClass;

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
	UPROPERTY(EditAnywhere, Category="Firing")
	float ProjectileBeginSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing")
	int MaxFiringsPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing")
	float RechargeTimePerProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing")
	int MagazineSize;


protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	float DeltaDegree;

private:
	FVector CalculateProjectileSpawnLocation();
	
	void IncreasePitch();
	void DecreasePitch();
	
	void IncreaseYaw();
	void DecreaseYaw();
	
	void IncreaseRoll();
	void DecreaseRoll();
};