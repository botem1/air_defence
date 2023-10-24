// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "Math/Vector.h"
#include "AirDefence/Public/AIController/ADAIController.h"

#include "ADDrone.generated.h"

UCLASS()
class AIRDEFENCE_API AADDrone : public APawn
{
	GENERATED_BODY()

public:
	AADDrone();

	UFUNCTION(BlueprintCallable)
	void Initialize(FVector InBeginLocation, FVector InEndLocation, float InInitialSpeed, float InAccelerationMagnitude);
	
protected:
	// BP-functions
protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* PropellerLeftStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* PropellerRightStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* BodyStaticMesh;

protected:
	UPROPERTY(EditAnywhere)
	FVector BeginLocation;

	UPROPERTY(EditAnywhere)
	FVector EndLocation;
	
	UPROPERTY(EditAnywhere)
	float InitialSpeed;

	UPROPERTY(EditAnywhere)
	float AccelerationMagnitude;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	FVector ComputeVelocity(FVector InVelocity, FVector InAcceleration, float DeltaTime);
	FVector ComputeLocationChange(FVector InLocation, FVector InVelocity, float DeltaTime);

	void UpdateVelocity(float DeltaTime);
	void UpdateLocation(float DeltaTime);
private:
	FVector Velocity;

	FVector Acceleration;
};
