#pragma once

#include "CoreMinimal.h"

#include "ClickerEconomySnapshot.generated.h"

USTRUCT(BlueprintType)
struct FClickerEconomySnapshot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32  UpgradeLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double Currency = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 LastSaveTime = 0;
};
