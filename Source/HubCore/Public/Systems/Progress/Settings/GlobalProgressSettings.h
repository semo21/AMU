// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GlobalProgressSettings.generated.h"

/**
 *
 */
UCLASS()
class HUBCORE_API UGlobalProgressSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Unlock", meta = (Categories = "Level"))
	FGameplayTagContainer InitialUnlockedLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Unlock", meta = (Categories = "Level"))
	TMap<FGameplayTag, double> UnlockPrices;
};
