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

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* BarrelStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent* FlakFoundationStaticMesh;
	
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
};