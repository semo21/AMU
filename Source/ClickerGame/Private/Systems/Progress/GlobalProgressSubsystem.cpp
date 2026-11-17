// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Progress/GlobalProgressSubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Progress/Settings/GlobalProgressSettings.h"

void UGlobalProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GlobalProgressSettings = GlobalProgressSettingsAsset.LoadSynchronous();
	UE_LOG(LogTemp, Log, TEXT("UGlobalProgressSubsystem::Initialize / ProgressSettings: %s"), GlobalProgressSettings ? TEXT("Loaded") : TEXT("Null"));
	
	SaveManagerRef = Collection.InitializeDependency<USaveManagerSubsystem>();
	if (SaveManagerRef) {
		SaveManagerRef->LoadProgress(GlobalProgressSnapshot);
	}

	if (GlobalProgressSettings && GlobalProgressSnapshot.UnlockedLevels.IsEmpty()) {
		GlobalProgressSnapshot.UnlockedLevels.AppendTags(GlobalProgressSettings->InitialUnlockedLevel);
	}
}

void UGlobalProgressSubsystem::Deinitialize()
{
	if (SaveManagerRef) {
		SaveManagerRef->SaveProgress(GlobalProgressSnapshot);
	}
	Super::Deinitialize();
}

bool UGlobalProgressSubsystem::IsLevelUnlocked(const FGameplayTag& LevelTag) const
{
	return GlobalProgressSnapshot.UnlockedLevels.HasTag(LevelTag);
}

void UGlobalProgressSubsystem::UnlockLevel(const FGameplayTag& LevelTag) {
	GlobalProgressSnapshot.UnlockedLevels.AddTag(LevelTag);
}