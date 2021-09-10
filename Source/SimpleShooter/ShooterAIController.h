// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

	public:

	// UPROPERTY(EditAnywhere)
	// float Radius = 200.0f;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviour;
	
	
	protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
