// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "MGP_2526Character.h"
#include "Templates/Casts.h"
#include "TimingComponent.h"

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	// editor crashed when i opened animation blueprint, have to check if world is three
	UWorld* World = MeshComp->GetWorld();
	if (!World || !World->IsGameWorld()) return;
	// DEFAULT OBJECT PROBLEMS 
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner || Owner->IsPendingKillPending()) return;

	AEnemy* Enemy = Cast<AEnemy>(Owner);
	if (!IsValid(Enemy)) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!IsValid(PC)) return;
	/// default object CRASH problems
	APawn* PlayerPawn = PC->GetPawn();
	if (!IsValid(PlayerPawn)) return;

	UTimingComponent* TimingComp = PlayerPawn->FindComponentByClass<UTimingComponent>();

	switch (NotifyType)
	{
	case ENotifyType::StartWindow:
		if (TimingComp)
		{
			TimingComp->StartTimingWindow(ETimingAction::Parry);

			// reset attempt lock
			AMGP_2526Character* PlayerChar = Cast<AMGP_2526Character>(PlayerPawn);
			if (PlayerChar)
			{
				PlayerChar->bParryPressedThisWindow = false;
			}
		}
		break;


	case ENotifyType::EndAttack:
		if (Enemy)
		{
			Enemy->bIsAttacking = false;
			
		}
		if (TimingComp)
		{
			TimingComp->bIsActive = false;
		}
		break;

	case ENotifyType::ApplyDamage:
		AMGP_2526Character* PlayerChar = Cast<AMGP_2526Character>(PlayerPawn);
		if (PlayerChar)
		{
			
			PlayerChar->TakeDamage(10.f);  // Apply 10 damage to the player
			UE_LOG(LogTemp, Warning, TEXT("Notify hit! Player Health is now: %f"), PlayerChar->Health);
		}
		break;
	}
}
