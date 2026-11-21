// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "MyPlayerControllerBase.generated.h"

UCLASS()
class HUBCORE_API AMyPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()	
public:
	UFUNCTION()	
	virtual void HandleActionButtonClicked(const FGameplayTag& ActionTag);
	virtual void RequestLevelUnlock(const FGameplayTag& LevelTag);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
