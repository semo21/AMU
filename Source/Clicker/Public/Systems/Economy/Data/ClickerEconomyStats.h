#pragma once

#include "CoreMinimal.h"

#include "ClickerEconomyStats.generated.h"

USTRUCT(BlueprintType)
struct FClickerEconomyStats 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	double Currency = 0.0;

	UPROPERTY(BlueprintReadOnly)
	int32  UpgradeLevel = 0;

	UPROPERTY(BlueprintReadOnly)
	double CurrencyPerClick = 0.0;

	UPROPERTY(BlueprintReadOnly)
	double CurrencyPerSecond = 0.0;

	UPROPERTY(BlueprintReadOnly)
	double UpgradeCost = 0.0;
};