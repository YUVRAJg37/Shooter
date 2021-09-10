// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:

	void Shoot();
	
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);

	void LookUp(float AxisValue);
	void LookSide(float AxisValue);

	void IncreaseSpeed();
	void DecreaseSpeed();
	bool isRunning;

	UPROPERTY(EditAnywhere)
	float Sensi = 30.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	float Maxhealth = 100;
	
	float Health;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UPROPERTY(EditAnywhere)
	float temp = 0.5f;

	void Interp(float DeltaTime);
	
};
