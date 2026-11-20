// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Progress/GlobalProgressSubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Progress/Settings/GlobalProgressSettings.h"

void UGlobalProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GlobalProgressSettings = GlobalProgressSettingsAsset.LoadSynchronous();
	check(GlobalProgressSettings);

	SaveManagerRef = Collection.InitializeDependency<USaveManagerSubsystem>();
	check(SaveManagerRef);

	SaveManagerRef->LoadProgress(GlobalProgressSnapshot);

	GlobalEconomyRef = Collection.InitializeDependency<UGlobalEconomySubsystem>();
	check(GlobalEconomyRef);

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

	const double* Price = GlobalProgressSettings->UnlockPrices.Find(LevelTag);
	if (!Price) {
		UE_LOG(LogTemp, Warning, TEXT("UGlobalProgressSubsystem::TryUnlockLevel / No price in the DA"));
		return false;
	}

	if (!GlobalEconomyRef->TrySpendGlobalCurrency(*Price)) {
		return false;
	}

	UnlockLevel(LevelTag);
	SaveManagerRef->SaveProgress(GlobalProgressSnapshot);
	return true;
}

void UGlobalProgressSubsystem::UnlockLevel(const FGameplayTag& LevelTag) {
	GlobalProgressSnapshot.UnlockedLevels.AddTag(LevelTag);
}