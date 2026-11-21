// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Systems/Progress/Data/GlobalProgressSnapshot.h"

#include "GlobalProgressSubsystem.generated.h"

class USaveManagerSubsystem;
class UGlobalProgressSettings;
class UGlobalEconomySubsystem;

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class HUBCORE_API UGlobalProgressSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category="Progress")
	bool IsLevelUnlocked(const FGameplayTag& LevelTag) const;
	UFUNCTION(BlueprintCallable, Category = "Progress")
	bool TryUnlockLevel(const FGameplayTag& LevelTag);
	UFUNCTION(BlueprintPure, Category="Progress")
	bool GetUnlockPrice(const FGameplayTag& LevelTag, double& OutPrice) const;
	const FGlobalProgressSnapshot& GetSnapshot() const { return GlobalProgressSnapshot; }

private:
	void UnlockLevel(const FGameplayTag& LevelTag);

	UPROPERTY()
	FGlobalProgressSnapshot GlobalProgressSnapshot;
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerRef;
	UPROPERTY()
	TObjectPtr<UGlobalEconomySubsystem> GlobalEconomyRef;
	UPROPERTY(Config)
	TSoftObjectPtr<UGlobalProgressSettings> GlobalProgressSettingsAsset;
	UPROPERTY(Transient)
	TObjectPtr<UGlobalProgressSettings> GlobalProgressSettings;
};
