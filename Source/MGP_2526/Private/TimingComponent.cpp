// Fill out your copyright notice in the Description page of Project Settings.


#include "TimingComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTimingComponent::UTimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsActive = false;

	//deafult timing windows
	Window.PerfectStart = 0.2f;
	Window.PerfectEnd = 0.3f;

	Window.GoodStart = 0.1f;
	Window.GoodEnd = 0.4f;

	Window.OkStart = 0.0f;
	Window.OkEnd = 0.5f;

	
}


// Called when the game starts
void UTimingComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}
void UTimingComponent::StartTimingWindow(ETimingAction ActionType)
{
	CurrentAction = ActionType;
	StartTime = GetWorld()->GetTimeSeconds();
	bIsActive = true;
}

ETimingResult UTimingComponent::EvaluateTiming()
{
    if (!GetWorld())
        return ETimingResult::Miss;

    if (!bIsActive)
        return ETimingResult::Miss;

    float CurrentTime = GetWorld()->GetTimeSeconds() - StartTime;
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,
        FString::Printf(TEXT("Time: %f"), CurrentTime));

    // Window expired
    if (CurrentTime > Window.OkEnd)
    {
        bIsActive = false;
        return ETimingResult::Miss;
    }

    if (CurrentTime >= Window.PerfectStart && CurrentTime <= Window.PerfectEnd)
    {
        bIsActive = false;
        return ETimingResult::Perfect;
    }

    if (CurrentTime >= Window.GoodStart && CurrentTime <= Window.GoodEnd)
    {
        bIsActive = false;
        return ETimingResult::Good;
    }

    if (CurrentTime >= Window.OkStart && CurrentTime <= Window.OkEnd)
    {
        bIsActive = false;
        return ETimingResult::Ok;
    }

    return ETimingResult::Miss;
}
