// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "TimingComponent.h"

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;
    AActor* Owner = MeshComp->GetOwner();
    if (!Owner || Owner->HasAnyFlags(RF_ClassDefaultObject)) return;

    // --- The Fix ---
    AEnemy* Enemy = Cast<AEnemy>(Owner);
    if (Enemy)
    {
        Enemy->bIsAttacking = false;
    }
    // ----------------

    UTimingComponent* TimingComp = Owner->FindComponentByClass<UTimingComponent>();
    if (TimingComp)
    {
        TimingComp->StartTimingWindow(ETimingAction::Parry);
    }
}