// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "TimingComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	TimingComponent = CreateDefaultSubobject<UTimingComponent>(TEXT("TimingComponent"));
	LastAttackTime = -10.0f;
	AttackCooldown = 2.0f;
	bIsAttacking = false;

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

	//calculate the direction to the player
	FVector TargetLocation = Player->GetActorLocation();
	FVector SelfLocation = GetActorLocation();
	FVector TargetDirection = (TargetLocation - SelfLocation).GetSafeNormal();

	
	FRotator TargetRotation = TargetDirection.Rotation();
	TargetRotation.Pitch = 0.f;
	TargetRotation.Roll = 0.f;

	FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 5.f);
	SetActorRotation(SmoothRotation);

	
	FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	AddMovementInput(Direction, 1.0f);

	float Distance = FVector::Dist(Player->GetActorLocation(), GetActorLocation());
	float TimeNow = GetWorld()->GetTimeSeconds();

	if (!bIsAttacking && Distance < 200.0f && TimeNow - LastAttackTime > AttackCooldown)
	{
		Attack();
		LastAttackTime = TimeNow;
		bIsAttacking = true;
	}
	else if (bIsAttacking)
	{
		
		GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Yellow, TEXT("Waiting for Notify to reset bIsAttacking..."));
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemy::Attack()
{
	if (!GetMesh()) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;
	AnimInstance->Montage_Play(AttackMontage);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Enemy Attack Animation"));

}

