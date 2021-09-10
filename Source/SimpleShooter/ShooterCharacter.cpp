// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = Maxhealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Gun->SetOwner(this);
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	Interp(DeltaTime);
	
	
	
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AShooterCharacter::MoveSide);

	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookSide", this, &AShooterCharacter::LookSide);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &AShooterCharacter::IncreaseSpeed);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &AShooterCharacter::DecreaseSpeed);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageApplied = FMath::Min(Health, DamageApplied);
	Health-=DamageApplied;

	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);
	
	return  Health;
}


void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue / (isRunning ? 1.5 : 6));
	
}

void AShooterCharacter::MoveSide(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue / (isRunning ? 1.5: 6));
}

void AShooterCharacter::LookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * Sensi * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookSide(float AxisValue) 
{
	AddControllerYawInput(AxisValue * Sensi * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::IncreaseSpeed() 
{
	isRunning = true;
}

void AShooterCharacter::DecreaseSpeed() 
{
	isRunning = false;
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

void AShooterCharacter::Interp(float DeltaTime)
{
	temp = FMath::FInterpConstantTo(6, 2.4, DeltaTime, 0.5f);
}

bool AShooterCharacter::IsDead() const
{
	if(Health==0)
	return true;
	else return  false;
}




