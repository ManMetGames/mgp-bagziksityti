// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "TimingComponent.h"

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	// editor crashed when i opened animation blueprint, have to check if world is three
	UWorld* World = MeshComp->GetWorld();
	if (!World || !World->IsGameWorld()) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner || Owner->HasAnyFlags(RF_ClassDefaultObject)) return;

	AEnemy* Enemy = Cast<AEnemy>(Owner);
	if (!Enemy) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC) return;

	APawn* PlayerPawn = PC->GetPawn();
	if (!PlayerPawn) return;

	UTimingComponent* TimingComp = PlayerPawn->FindComponentByClass<UTimingComponent>();

	switch (NotifyType)
	{
	case ENotifyType::StartWindow:
		if (TimingComp)
		{
			TimingComp->StartTimingWindow(ETimingAction::Parry);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Timing Window START"));
		}
		break;

	case ENotifyType::EndAttack:
		if (Enemy)
		{
			Enemy->bIsAttacking = false;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Attack End"));
		}
		break;
	}
}
