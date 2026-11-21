// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Systems/Economy/Data/GlobalEconomySnapshot.h"
#include "Systems/Progress/Data/GlobalProgressSnapshot.h"

#include "GameFramework/SaveGame.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"

#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HUBCORE_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:	
	UPROPERTY(SaveGame) TMap<FGameplayTag, FInstancedStruct> LevelSnapshots;
	UPROPERTY(SaveGame) FGlobalEconomySnapshot GlobalEconomySnapshot;
	UPROPERTY(SaveGame) FGlobalProgressSnapshot GlobalProgressSnapshot;
};
