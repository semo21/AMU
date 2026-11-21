// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GameMode/MyGameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HUBCORE_API ALobbyGameMode : public AMyGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
