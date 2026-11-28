// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Systems/MyWorldSubsystemBase.h"
#include "Systems/Economy/Data/ClickerEconomySnapshot.h"
#include "Systems/Economy/Data/ClickerEconomyStats.h"

#include "ClickerEconomySubsystem.generated.h"

class UClickerUISubsystem;
class USaveManagerSubsystem;
class UClickerEconomySettings;
class UGlobalEconomySubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChanged, const FClickerEconomyStats&, Stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassiveIncome, double, AmountPerSec);

/**
 *
 */
UCLASS(BlueprintType, Config=Game, DefaultConfig)
class CLICKER_API UClickerEconomySubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void StartWorld();
	double OnClicked();
	bool TryUpgrade();
	bool TryExchange();
	void RequestSave();
	bool RequestLoad();

	UFUNCTION(BlueprintPure, Category = "Economy") 
	FClickerEconomyStats GetStats() const;

	UFUNCTION(BlueprintPure) 
	double GetLastOfflineReward() const { return LastOfflineReward; }

	// Delegate
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnEconomyChanged OnEconomyChanged;
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnPassiveIncome OnPassiveIncome;

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;

private:
	void Broadcast();
	void StartAutoSaveTimer();
	void StartTickTimer();
	void OnTick1Second();
	void StopAutoSaveTimer();
	void StopTickTimer();
	double GetCurrencyPerClick() const;
	double GetCurrencyPerSecond() const;
	double GetUpgradeCost() const;
	void ApplySnapshot(const FClickerEconomySnapshot& In);
	void UpdateLastOfflineReward();

	UPROPERTY(Config)
	TSoftObjectPtr<UClickerEconomySettings> ClickerEconomySettingsAsset;

	UPROPERTY(Transient)
	TObjectPtr<UClickerEconomySettings> ClickerEconomySettings;

	UPROPERTY()
	TObjectPtr<UGlobalEconomySubsystem> GlobalEconomySubsystemRef;

	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerSubsystemRef;

	FClickerEconomySnapshot ClickerEconomySnapshot;
	FTimerHandle AutoSaveHandle;
	FTimerHandle TickHandle;
	bool bWorldStarted = false;
	double LastOfflineReward = 0.0;
};
