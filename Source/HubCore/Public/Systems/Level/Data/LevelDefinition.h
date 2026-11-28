// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "LevelDefinition.generated.h"

/**
 *
 */
UCLASS()
class HUBCORE_API ULevelDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Level", meta = (Categories = "Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly, Category = "Level")
	TSoftObjectPtr<UWorld> Map;

	UPROPERTY(EditDefaultsOnly, Category = "Unlock")
	double UnlockPrice = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = "Display")
	FText LevelDisplayName;
};
