// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "DrawDebugHelpers.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Mesh->SetupAttachment(Root);
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	AShooterCharacter* OwnerPawn = Cast<AShooterCharacter>(GetOwner());
	if(OwnerPawn == nullptr) return;

	AController* OwnerPawnController = OwnerPawn->GetController();
	if(OwnerPawnController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	
	OwnerPawnController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult FHitResult;

	bool LineTrace = GetWorld()->UWorld::LineTraceSingleByChannel(FHitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if(LineTrace)
	{
		FVector ShootDirection = -Rotation.Vector();
		// DrawDebugPoint(GetWorld(), FHitResult.Location, 20.0f, FColor::Red, true, 5.0f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactHit, FHitResult.Location, ShootDirection.Rotation());

		AActor* HitActor = FHitResult.GetActor();
		if(HitActor!=nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, FHitResult, ShootDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerPawnController, this );
		}
		
	}
	
}


