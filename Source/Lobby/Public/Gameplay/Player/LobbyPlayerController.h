// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"

#include "GameplayTagContainer.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LOBBY_API ALobbyPlayerController : public AMyPlayerControllerBase
{
	GENERATED_BODY()

public:
	virtual void RequestLevelUnlock(const FGameplayTag& LevelTag) override;
};
