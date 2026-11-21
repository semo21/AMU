// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GameMode/MyGameModeBase.h"

#include "ClickerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HUBCORE_API AClickerGameMode : public AMyGameModeBase
{
	GENERATED_BODY()
	
public:
	AClickerGameMode();
protected:
	virtual void BeginPlay() override;
};
