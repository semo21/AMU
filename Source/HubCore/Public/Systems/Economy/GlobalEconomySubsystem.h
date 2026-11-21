// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Systems/Economy/Data/GlobalEconomySnapshot.h"

#include "GlobalEconomySubsystem.generated.h"

class USaveManagerSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalEconomyChanged, const FGlobalEconomySnapshot&, Snapshot);
/**
 *
 */
UCLASS()
class HUBCORE_API UGlobalEconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddGlobalCurrency(double Amount);
	UFUNCTION(BlueprintCallable, Category = "Economy|Global")
	bool TrySpendGlobalCurrency(double Amount);
	UFUNCTION(BlueprintPure, Category = "Economy|Global")
	const FGlobalEconomySnapshot& GetSnapshot() const { return GlobalEconomySnapshot; }
	UPROPERTY(BlueprintAssignable, Category="Economy|Global")
	FOnGlobalEconomyChanged OnGlobalEconomyChanged;

private:
	UPROPERTY()
	FGlobalEconomySnapshot GlobalEconomySnapshot;
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerRef;
};
