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

	void Initialize(const TArray<AADDrone*>& InDrones);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	TArray<AADDrone*> Drones;
};
