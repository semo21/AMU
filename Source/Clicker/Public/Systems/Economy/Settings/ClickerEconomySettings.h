// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClickerEconomySettings.generated.h"

/**
 *
 */
UCLASS()
class CLICKER_API UClickerEconomySettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Economy") 
	double BaseCurrencyPerClick = 1.0;

	UPROPERTY(EditDefaultsOnly, Category = "Economy") 
	double CurrencyPerClickPerLevel = 1.0;

	UPROPERTY(EditDefaultsOnly, Category = "Economy") 
	double BaseCurrencyPerSecond = 2.0;

	UPROPERTY(EditDefaultsOnly, Category = "Economy")
	double CurrencyPerSecondPerLevel = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "Economy") 
	double BaseUpgradeCost = 10.0;

	UPROPERTY(EditDefaultsOnly, Category = "Economy") 
	double UpgradeCostMultiplier = 1.5;

	UPROPERTY(EditDefaultsOnly, Category = "Economy")
	int64 OfflineRewardMaxSeconds = 28800;	// 8h
};
