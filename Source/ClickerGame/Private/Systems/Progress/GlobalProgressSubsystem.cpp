// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Progress/GlobalProgressSubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Progress/Settings/GlobalProgressSettings.h"

void UGlobalProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GlobalProgressSettings = GlobalProgressSettingsAsset.LoadSynchronous();
	checkf(GlobalProgressSettings, TEXT("DA_GlobalProgressSettings failed to load"));

	SaveManagerRef = Collection.InitializeDependency<USaveManagerSubsystem>();
	checkf(SaveManagerRef, TEXT("SaveManagerRef failed to load"));

	SaveManagerRef->LoadProgress(GlobalProgressSnapshot);

	GlobalEconomyRef = Collection.InitializeDependency<UGlobalEconomySubsystem>();
	checkf(GlobalEconomyRef,TEXT("GlobalEconomyRef failed to load"));

	GlobalProgressSnapshot.UnlockedLevels.AppendTags(GlobalProgressSettings->InitialUnlockedLevel);
}

void UGlobalProgressSubsystem::Deinitialize()
{
	SaveManagerRef->SaveProgress(GlobalProgressSnapshot);
	Super::Deinitialize();
}

bool UGlobalProgressSubsystem::IsLevelUnlocked(const FGameplayTag& LevelTag) const
{
	return GlobalProgressSnapshot.UnlockedLevels.HasTag(LevelTag);
}

bool UGlobalProgressSubsystem::TryUnlockLevel(const FGameplayTag& LevelTag) {
	if (IsLevelUnlocked(LevelTag)) {
		UE_LOG(LogTemp, Warning, TEXT("UGlobalProgressSubsystem::TryUnlockLevel / %s Level is already unlocked"), *LevelTag.ToString());
		return false;
	}

	double Price = 0.0;
	if (!GetUnlockPrice(LevelTag, Price)) {
		UE_LOG(LogTemp, Warning, TEXT("UGlobalProgressSubsystem::TryUnlockLevel / No price in the DA"));
		return false;
	}

	if (!GlobalEconomyRef->TrySpendGlobalCurrency(Price)) {
		return false;
	}

	UnlockLevel(LevelTag);
	SaveManagerRef->SaveProgress(GlobalProgressSnapshot);
	return true;
}

bool UGlobalProgressSubsystem::GetUnlockPrice(const FGameplayTag& LevelTag, double& OutPrice) const {
	const double* Price = GlobalProgressSettings->UnlockPrices.Find(LevelTag);
	if (!Price) {		
		return false;
	}

	OutPrice = *Price;
	return true;
}

void UGlobalProgressSubsystem::UnlockLevel(const FGameplayTag& LevelTag) {
	GlobalProgressSnapshot.UnlockedLevels.AddTag(LevelTag);
}