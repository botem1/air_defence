// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"


#include "ADProjectile.generated.h"

class AADDrone;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class AIRDEFENCE_API AADProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AADProjectile();

public:
	UFUNCTION(BlueprintCallable)
	FVector GetProjectileLocation();

	UFUNCTION(BlueprintCallable)
	void SetProjectileLocation(FVector NewLocation);
	
	UFUNCTION(BlueprintCallable)
	FRotator GetProjectileRotation();

	UFUNCTION(BlueprintCallable)
	void SetProjectileRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable)
	void Initialize(FVector InitialDirection, float InitialSpeed, AActor* InTarget = nullptr);

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* ProjectileStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile Movement Component")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* NiagaraSystemExplosion;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* SoundExplosion;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	AADDrone* DroneToReach;
};
