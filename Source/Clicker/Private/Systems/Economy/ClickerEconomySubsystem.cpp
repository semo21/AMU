// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/ClickerEconomySubsystem.h"

#include "Gameplay/GameMode/ClickerGameMode.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "InstancedStruct.h"
#include "NativeGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Level_Clicker, "Level.Clicker");

void UClickerEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UClickerEconomySubsystem::Deinitialize() {
	RequestSave();
	StopAutoSaveTimer(); 
	StopTickTimer();

	Super::Deinitialize();
}

void UClickerEconomySubsystem::StartWorld(UWorld* World) {
	if (!World || bWorldStarted) return;

	bWorldStarted = true;

	if (UGameInstance* GI = World->GetGameInstance()) {
		SaveManagerSubsystemRef = GI->GetSubsystem<USaveManagerSubsystem>();
	}

	RequestLoad();
	StartAutoSaveTimer();
	StartTickTimer();
}

void UClickerEconomySubsystem::OnClicked() {
	ClickerEconomySnapshot.Currency += ClickerEconomySnapshot.CurrencyPerClick;
	Broadcast();
}

void UClickerEconomySubsystem::OnTick1Second() {
	ClickerEconomySnapshot.Currency += ClickerEconomySnapshot.CurrencyPerSecond;
	OnPassiveIncome.Broadcast(ClickerEconomySnapshot.CurrencyPerSecond);
	Broadcast();
}

bool UClickerEconomySubsystem::TryUpgrade() {
	const double UpgradeCost = GetUpgradeCost();
	if (ClickerEconomySnapshot.Currency < UpgradeCost) {
		return false;
	}
	ClickerEconomySnapshot.Currency -= UpgradeCost;
	ClickerEconomySnapshot.UpgradeLevel++;
	ClickerEconomySnapshot.CurrencyPerClick += 1.0;
	ClickerEconomySnapshot.CurrencyPerSecond += 0.5;

	Broadcast();
	RequestSave();
	return true;
}

void UClickerEconomySubsystem::RequestSave() {
	if (SaveManagerSubsystemRef) {
		FClickerEconomySnapshot Out = MakeSnapshot();
		Out.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

		SaveManagerSubsystemRef->SaveLevelSnapshot(TAG_Level_Clicker, FInstancedStruct::Make(Out));
	}
}

void UClickerEconomySubsystem::RequestLoad() {
	if (SaveManagerSubsystemRef) {
		FInstancedStruct Saved;
		if (SaveManagerSubsystemRef->LoadLevelSnapshot(TAG_Level_Clicker, Saved)) {
			if (const FClickerEconomySnapshot* Loaded = Saved.GetPtr<FClickerEconomySnapshot>()) {
				FClickerEconomySnapshot In = *Loaded;
				UpdateLastOfflineReward(In);
				ApplySnapshot(In);
				RequestSave();
				return;
			}			
		}
		Broadcast();
	}
}

TSubclassOf<AGameModeBase> UClickerEconomySubsystem::GetRequiredGameModeClass() const {
	return AClickerGameMode::StaticClass();
}

double UClickerEconomySubsystem::GetUpgradeCost() const {
	return FMath::Pow(ClickerEconomySnapshot.UpgradeGrowth, ClickerEconomySnapshot.UpgradeLevel + 1) * ClickerEconomySnapshot.UpgradeCostBase;
}

void UClickerEconomySubsystem::Broadcast() {
	OnEconomyChanged.Broadcast(ClickerEconomySnapshot);
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

FClickerEconomySnapshot UClickerEconomySubsystem::MakeSnapshot() const {
	return ClickerEconomySnapshot;
}

void UClickerEconomySubsystem::ApplySnapshot(const FClickerEconomySnapshot& In) {

	ClickerEconomySnapshot = In;
	Broadcast();
}

void UClickerEconomySubsystem::UpdateLastOfflineReward(FClickerEconomySnapshot& In) {
	// Offline Reward max 8 hours
	const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
	const int64 DeltaSec = 
		(Now - In.LastSaveTime > 28800) ? 
		28800 : (Now - In.LastSaveTime);
	
	LastOfflineReward = In.CurrencyPerSecond * DeltaSec;
	In.Currency += GetLastOfflineReward();
}