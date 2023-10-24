// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/ADProjectile.h"


DEFINE_LOG_CATEGORY_STATIC(LogADProjectile, All, All)

AADProjectile::AADProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AADProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

