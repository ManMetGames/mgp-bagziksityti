// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimingComponent.generated.h"

UENUM(BlueprintType)
enum class ETimingAction : uint8
{
	None,
	Parry,
	Block,
	SpecialAttack
};

UENUM(BlueprintType)
enum class ETimingResult : uint8
{
	None,
	Ok,
	Good,
	Perfect,
	Miss
};
USTRUCT(BlueprintType)
struct FTimingWindow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PerfectStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PerfectEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoodStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoodEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OkStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OkEnd;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MGP_2526_API UTimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTimingComponent();
	void StartTimingWindow(ETimingAction ActionType);
	ETimingResult EvaluateTiming();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float StartTime;
	bool bIsActive;

	ETimingAction CurrentAction;

	UPROPERTY(EditAnywhere)
	FTimingWindow Window;
		
};
