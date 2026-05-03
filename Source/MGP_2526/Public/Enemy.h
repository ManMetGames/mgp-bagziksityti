// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimingComponent.h"
#include "Animation/AnimMontage.h"
#include "Enemy.generated.h"


class TimingComponent;
UCLASS()
class MGP_2526_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatCollider")
	class USphereComponent* CombatCollider;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCombatColliderActive(bool bIsEnabled);
	void GreenCollider();

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 100.f;


	UPROPERTY()
	AActor* Player;

	float LastAttackTime;
	float AttackCooldown;
	bool bIsAttacking;
	bool bPerfectWindowTriggered = false;
	

	// Attack
	void Attack();
	

	// Timing system
	UPROPERTY(VisibleAnywhere)
	UTimingComponent* TimingComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
