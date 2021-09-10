// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	
	if(AIBehaviour!= nullptr)
	{
		RunBehaviorTree(AIBehaviour);

		
	}
	
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if(LineOfSightTo(PlayerPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Focusing"));
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("lastLocation"),PlayerPawn->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Focusing"));
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
	
}