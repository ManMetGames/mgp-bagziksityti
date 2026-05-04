// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "TimingComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	CombatCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CombatCollider"));
	CombatCollider->SetupAttachment(GetMesh(), TEXT("HandSocket"));
	CombatCollider->SetSphereRadius(50.f);
	CombatCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCollider->ComponentTags.Add(FName("EnemyAttack"));
	TimingComponent = CreateDefaultSubobject<UTimingComponent>(TEXT("TimingComponent"));
	LastAttackTime = -10.0f;     //so enemy can attack immediately at the start of the game
	AttackCooldown = 2.0f;
	bIsAttacking = false;
	CurrentHealth = MaxHealth;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GreenCollider();
	if (!GetWorld() || !Player) return;
	
	//calculate the direction to the player
	FVector TargetLocation = Player->GetActorLocation();
	FVector SelfLocation = GetActorLocation();
	//normal vektor
	FVector TargetDirection = (TargetLocation - SelfLocation).GetSafeNormal();

	// rotation for animation
	FRotator TargetRotation = TargetDirection.Rotation();
	// lock pitch and roll to prevent tilting 
	TargetRotation.Pitch = 0.f; // Y axis rotation 
	TargetRotation.Roll = 0.f;  // X axis rotation 

	//RInterp for shortest path from current rotation to target rotation, 5.f is the speed of rotation 
	FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 5.f);
	SetActorRotation(SmoothRotation);

	
	FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	// Add movement input in the direction of the player with a scale of 1.0f (full speed)
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
		
		//UE_LOG(LogTemp, Display, TEXT("notify resetting boolean bisAttacking"));
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


}
void AEnemy::SetCombatColliderActive(bool bIsEnabled)
{
	if (!CombatCollider) return;
	if (bIsEnabled)
	{
		CombatCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		CombatCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bIsAttacking = false;
	}
}
void AEnemy::GreenCollider()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;
	UTimingComponent* PlayerTiming = PlayerPawn->FindComponentByClass<UTimingComponent>();
	if (!PlayerTiming)
		return;
	if (!PlayerTiming->bIsActive)
	{
		bPerfectWindowTriggered = false;
		return;
	}
	if (PlayerTiming->IsInPerfectWindow() && !bPerfectWindowTriggered)
	{
		bPerfectWindowTriggered = true;
		DrawDebugSphere(GetWorld(), CombatCollider->GetComponentLocation(), sphereRadius, 12, FColor::Green, false, 0.1f, 0, 10.f);
	}
	
	

	/*if (TimingComponent && TimingComponent->IsInPerfectWindow())
	{
		UE_LOG(LogTemp, Warning, TEXT("!!! PERFECT WINDOW ACTIVE - DRAWING SPHERE !!!"));
		CombatCollider->SetSphereRadius(75.f);
		DrawDebugSphere(GetWorld(), CombatCollider->GetComponentLocation(),
			CombatCollider->GetScaledSphereRadius(), 12, FColor::Green, false, 0.05f, 0, 15.0f);
	}
	else
		{
		CombatCollider->SetSphereRadius(50.f);
	}*/

}