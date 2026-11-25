// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/DefenseEconomySubsystem.h"
#include "Gameplay/GameMode/DefenseGameMode.h"
#include "Systems/Economy/Settings/DefenseEconomySettings.h"

void UDefenseEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	
	DefenseEconomySettings = DefenseEconomySettingsAsset.LoadSynchronous();
	UE_LOG(LogTemp, Log, TEXT("UDefenseEconomySubsystem::Initialize / EconomySettings: %s"), DefenseEconomySettings ? TEXT("Loaded") : TEXT("Null"));
}

TSubclassOf<AGameModeBase> UDefenseEconomySubsystem::GetRequiredGameModeClass() const {
	return ADefenseGameMode::StaticClass();
}

double UDefenseEconomySubsystem::CalculateSettlementReward(EDefenseMatchState Result) const {
	switch (Result) {
	case EDefenseMatchState::Victory:
		return DefenseEconomySettings ? DefenseEconomySettings->VictoryReward : 0.0;
	case EDefenseMatchState::Defeat:
		return DefenseEconomySettings ? DefenseEconomySettings->DefeatReward : 0.0;
	default:
		return 0.0;
	}
}