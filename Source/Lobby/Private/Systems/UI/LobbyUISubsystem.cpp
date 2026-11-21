// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/LobbyUISubsystem.h"

#include "Gameplay/GameMode/LobbyGameMode.h"

#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Progress/GlobalProgressSubsystem.h"
#include "Systems/UI/GlobalUISubsystem.h"
#include "Systems/UI/Widgets/Root/LobbyHUDRootWidget.h"
#include "Systems/UI/Widgets/Modal/LobbyUnlockConfirmWidget.h"
#include "Systems/UI/Settings/LobbyUISettings.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"



void ULobbyUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	UISettings = UISettingsAsset.LoadSynchronous();
	checkf(UISettings, TEXT("DA_LobbyUISettings failed to load."));

	UE_LOG(LogTemp, Warning, TEXT("ULobbyUISubsystem::Initialize"));
}

void ULobbyUISubsystem::Deinitialize() {
	if (UGameInstance* GI = GetWorld()->GetGameInstance()) {
		if (auto* GlobalEco = GI->GetSubsystem<UGlobalEconomySubsystem>()) {
			GlobalEco->OnGlobalEconomyChanged.RemoveDynamic(this, &ULobbyUISubsystem::HandleGlobalEconomyChanged);
		}
	}

	Super::Deinitialize();
}

TSubclassOf<AGameModeBase> ULobbyUISubsystem::GetRequiredGameModeClass() const {
	return ALobbyGameMode::StaticClass();
}

void ULobbyUISubsystem::InitializeHUD() {
	UGameInstance* GI = GetWorld()->GetGameInstance();

	auto* GlobalUI = GI->GetSubsystem<UGlobalUISubsystem>();
	if (!ensure(GlobalUI)) return;

	LobbyRoot = Cast<ULobbyHUDRootWidget>(GlobalUI->GetCurrentRootWidget());
	if (!ensure(LobbyRoot)) return;

	auto* GlobalEco = GI->GetSubsystem<UGlobalEconomySubsystem>();
	if (!ensure(GlobalEco)) return;

	LobbyRoot->SetGlobalCurrency(GlobalEco->GetSnapshot().GlobalCurrency);
	GlobalEco->OnGlobalEconomyChanged.AddDynamic(this, &ULobbyUISubsystem::HandleGlobalEconomyChanged);
}

void ULobbyUISubsystem::HandleGlobalEconomyChanged(const FGlobalEconomySnapshot& Snapshot) {
	LobbyRoot->SetGlobalCurrency(Snapshot.GlobalCurrency);
}

void ULobbyUISubsystem::ShowUnlockConfirm(const FGameplayTag& LevelTag) {
	UGameInstance* GI = GetWorld()->GetGameInstance();
	auto* GlobalProgress = GI->GetSubsystem<UGlobalProgressSubsystem>();
	auto* GlobalEco = GI->GetSubsystem<UGlobalEconomySubsystem>();

	double Price = 0.0;
	if (!GlobalProgress->GetUnlockPrice(LevelTag, Price)) {
		UE_LOG(LogTemp, Warning, TEXT("ULobbyUISubsystem::ShowUnlockConfirm / %s has no unlock price"), *LevelTag.ToString());
		return;
	}

	if (!UnlockConfirmWidget) {
		UnlockConfirmWidget = CreateWidget<ULobbyUnlockConfirmWidget>(GetWorld()->GetFirstPlayerController(), UISettings->UnlockConfirmWidgetClass);
		UnlockConfirmWidget->OnConfirmed.AddDynamic(this, &ULobbyUISubsystem::HandleUnlockConfirmed);
		UnlockConfirmWidget->OnCancelled.AddDynamic(this, &ULobbyUISubsystem::HandleUnlockCancelled);
	}

	const FText* LevelName = UISettings->LevelDisplayNames.Find(LevelTag);
	PendingUnlockLevel = LevelTag;
	UnlockConfirmWidget->SetUnlockInfo(LevelName ? *LevelName : FText::FromString(LevelTag.ToString()), Price, GlobalEco->GetSnapshot().GlobalCurrency);
	LobbyRoot->ShowModal(UnlockConfirmWidget);
}

void ULobbyUISubsystem::HandleUnlockConfirmed() {
	auto* GlobalProgress = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalProgressSubsystem>();

	GlobalProgress->TryUnlockLevel(PendingUnlockLevel);
	LobbyRoot->ClearModal();
}

void ULobbyUISubsystem::HandleUnlockCancelled() {
	LobbyRoot->ClearModal();
}