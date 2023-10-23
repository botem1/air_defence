// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ADProjectile.generated.h"

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
	FVector GetProjectileVelocity();

	UFUNCTION(BlueprintCallable)
	void SetProjectileVelocity(FVector NewVelocity);
	
	UFUNCTION(BlueprintCallable)
	void Initialize(FVector InitialDirection);

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* ProjectileStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile Movement Component")
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	FVector Velocity;
	
	bool bIsMotionEnabled;
};
