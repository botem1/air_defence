// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/ADAIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogADAIController, All, All)

AADAIController::AADAIController(FObjectInitializer const& ObjectInitializer)
{
	
}

void AADAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
