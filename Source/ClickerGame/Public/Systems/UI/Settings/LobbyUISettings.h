// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "LobbyUISettings.generated.h"

class ULobbyUnlockConfirmWidget;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API ULobbyUISettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<ULobbyUnlockConfirmWidget> UnlockConfirmWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category="UI", meta=(Categories="Level"))
	TMap<FGameplayTag, FText> LevelDisplayNames;
};
