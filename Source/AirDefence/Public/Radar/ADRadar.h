// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Containers/Array.h"

#include "ADRadar.generated.h"

class AADDrone;

UCLASS()
class AIRDEFENCE_API AADRadar : public AActor
{
	GENERATED_BODY()
	
public:
	AADRadar();
	
	UFUNCTION(BlueprintCallable)
	AADDrone* GetCurrentDroneWithinRadius(FVector Location, float Radius);

	UFUNCTION(BlueprintCallable)
	FVector GetCurrentDroneLastTickLocation();
	
	void Initialize(AADDrone* InDrone);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	AADDrone* CurrentDrone;

	FVector LastDroneLocation;
};
