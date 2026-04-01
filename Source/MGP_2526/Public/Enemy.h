// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimingComponent.h"
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
	UPROPERTY()
	AActor* Player;

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
