// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimingComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimingComponent = CreateDefaultSubobject<UTimingComponent>(TEXT("TimingComponent"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!Player) return;

	// Move toward player
	FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	AddMovementInput(Direction, 1.0f);

	// Distance check
	float Distance = FVector::Dist(Player->GetActorLocation(), GetActorLocation());

	if (Distance < 200.0f)
	{
		Attack();
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemy::Attack()
{
	if (!TimingComponent) return;

	// TEMP: trigger timing window manually
	TimingComponent->StartTimingWindow(ETimingAction::Parry);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Enemy Attack!"));
}

