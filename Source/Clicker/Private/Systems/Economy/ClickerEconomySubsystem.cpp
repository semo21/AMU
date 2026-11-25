// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/ClickerEconomySubsystem.h"

#include "Gameplay/GameMode/ClickerGameMode.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"
#include "Systems/Economy/Settings/ClickerEconomySettings.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "InstancedStruct.h"
#include "NativeGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Level_Clicker, "Level.Clicker");

void UClickerEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	ClickerEconomySettings = ClickerEconomySettingsAsset.LoadSynchronous();
	checkf(ClickerEconomySettings, TEXT("ClickerEconomySettingsAsset is not loaded."));
}

void UClickerEconomySubsystem::Deinitialize() {
	if (bWorldStarted) {
		RequestSave();
		StopAutoSaveTimer();
		StopTickTimer();
	}

	Super::Deinitialize();
}

void UClickerEconomySubsystem::StartWorld() {
	bWorldStarted = true;

	SaveManagerSubsystemRef = GetWorld()->GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();
	check(SaveManagerSubsystemRef);

	if (RequestLoad()) {
		UpdateLastOfflineReward();
		RequestSave();
	}
	Broadcast();

	StartAutoSaveTimer();
	StartTickTimer();
}

double UClickerEconomySubsystem::OnClicked() {
	const double Amount = GetCurrencyPerClick();
	ClickerEconomySnapshot.Currency += Amount;
	Broadcast();

	return Amount;
}

void UClickerEconomySubsystem::OnTick1Second() {
	const double Amount = GetCurrencyPerSecond();

	ClickerEconomySnapshot.Currency += Amount;
	OnPassiveIncome.Broadcast(Amount);
	Broadcast();
}

FClickerEconomyStats UClickerEconomySubsystem::GetStats() const{
	FClickerEconomyStats Stats;
	Stats.Currency = ClickerEconomySnapshot.Currency;
	Stats.UpgradeLevel = ClickerEconomySnapshot.UpgradeLevel;
	Stats.CurrencyPerClick = GetCurrencyPerClick();
	Stats.CurrencyPerSecond = GetCurrencyPerSecond();
	Stats.UpgradeCost = GetUpgradeCost();

	return Stats;
}

bool UClickerEconomySubsystem::TryUpgrade() {
	const double UpgradeCost = GetUpgradeCost();
	if (ClickerEconomySnapshot.Currency < UpgradeCost) {
		return false;
	}
	ClickerEconomySnapshot.Currency -= UpgradeCost;
	ClickerEconomySnapshot.UpgradeLevel++;

	Broadcast();
	RequestSave();
	return true;
}

void UClickerEconomySubsystem::RequestSave() {
	ClickerEconomySnapshot.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

	SaveManagerSubsystemRef->SaveLevelSnapshot(TAG_Level_Clicker, FInstancedStruct::Make(ClickerEconomySnapshot));
}

bool UClickerEconomySubsystem::RequestLoad() {
	FInstancedStruct Saved;
	if (!SaveManagerSubsystemRef->LoadLevelSnapshot(TAG_Level_Clicker, Saved)) return false;

	const FClickerEconomySnapshot* Loaded = Saved.GetPtr<FClickerEconomySnapshot>();
	if (!Loaded) return false;

	ApplySnapshot(*Loaded);
	return true;
}

TSubclassOf<AGameModeBase> UClickerEconomySubsystem::GetRequiredGameModeClass() const {
	return AClickerGameMode::StaticClass();
}

double UClickerEconomySubsystem::GetCurrencyPerClick() const {
	// baseCPC + (CPC per level * upgrade level)
	return ClickerEconomySettings->BaseCurrencyPerClick + ClickerEconomySettings->CurrencyPerClickPerLevel * ClickerEconomySnapshot.UpgradeLevel;
}

double UClickerEconomySubsystem::GetCurrencyPerSecond() const {
	// baseCPS + (CPS per level * upgrade level)
	return ClickerEconomySettings->BaseCurrencyPerSecond + ClickerEconomySettings->CurrencyPerSecondPerLevel * ClickerEconomySnapshot.UpgradeLevel;
}

double UClickerEconomySubsystem::GetUpgradeCost() const {
	// base upgrade cost * (upgrade cost multiplier ^ upgrade level)
	return ClickerEconomySettings->BaseUpgradeCost * FMath::Pow(ClickerEconomySettings->UpgradeCostMultiplier, ClickerEconomySnapshot.UpgradeLevel);
}

void UClickerEconomySubsystem::Broadcast() {
	OnEconomyChanged.Broadcast(GetStats());
}

void UClickerEconomySubsystem::StartAutoSaveTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().SetTimer(
			AutoSaveHandle,
			FTimerDelegate::CreateUObject(this, &UClickerEconomySubsystem::RequestSave),
			60.0f,
			true
		);
	}
}

void UClickerEconomySubsystem::StartTickTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().SetTimer(
			TickHandle,
			this, &UClickerEconomySubsystem::OnTick1Second,
			1.0f,
			true
		);
	}
}

void UClickerEconomySubsystem::StopAutoSaveTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().ClearTimer(AutoSaveHandle);
	}
}

void UClickerEconomySubsystem::StopTickTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().ClearTimer(TickHandle);
	}
}

void UClickerEconomySubsystem::ApplySnapshot(const FClickerEconomySnapshot& In) {

	ClickerEconomySnapshot = In;
	Broadcast();
}

void UClickerEconomySubsystem::UpdateLastOfflineReward() {
	const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
	const int64 DeltaSec = FMath::Min(Now - ClickerEconomySnapshot.LastSaveTime, ClickerEconomySettings->OfflineRewardMaxSeconds);
		
	LastOfflineReward = GetCurrencyPerSecond() * DeltaSec;
	ClickerEconomySnapshot.Currency += LastOfflineReward;
}