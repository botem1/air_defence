// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "Math/Vector.h"

#include "ADDrone.generated.h"

UCLASS()
class AIRDEFENCE_API AADDrone : public APawn
{
	GENERATED_BODY()

public:
	AADDrone();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// BP-functions
protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* DroneBoxStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* DroneSphereStaticMesh;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
private:
	// private properties
private:
	// private functions
	
};
