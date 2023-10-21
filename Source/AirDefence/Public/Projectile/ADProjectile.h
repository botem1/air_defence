// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ADProjectile.generated.h"

UCLASS()
class AIRDEFENCE_API AADProjectile : public APawn
{
	GENERATED_BODY()
	
public:
	AADProjectile();
	
	UFUNCTION(BlueprintCallable)
	void Initialize(FVector SpawnDirection, AActor* InTarget);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	UStaticMeshComponent* ProjectileStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;
};
