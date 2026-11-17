// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/LobbyUISubsystem.h"
#include "Gameplay/GameMode/LobbyGameMode.h"
#include "Systems/UI/GlobalUISubsystem.h"
#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/UI/Widgets/Root/LobbyHUDRootWidget.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"



void ULobbyUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("ULobbyUISubsystem::Initialize"));
}

TSubclassOf<AGameModeBase> ULobbyUISubsystem::GetRequiredGameModeClass() const {
	return ALobbyGameMode::StaticClass();
}

void ULobbyUISubsystem::InitializeHUD() {
	UGameInstance* GI = GetWorld()->GetGameInstance();

	auto* GlobalUI = GI->GetSubsystem<UGlobalUISubsystem>();
	if (!ensure(GlobalUI)) return;

	auto* Root = Cast<ULobbyHUDRootWidget>(GlobalUI->GetCurrentRootWidget());
	if (!ensure(Root)) return;

	auto* GlobalEco = GI->GetSubsystem<UGlobalEconomySubsystem>();
	if (!ensure(GlobalEco)) return;

	Root->SetGlobalCurrency(GlobalEco->GetSnapshot().GlobalCurrency);

}