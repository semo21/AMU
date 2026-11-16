// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/LobbyGameMode.h"
#include "Systems/UI/LobbyUISubsystem.h"

void ALobbyGameMode::BeginPlay() {
	Super::BeginPlay();

	if (auto* LobbyUI = GetWorld()->GetSubsystem<ULobbyUISubsystem>()) {
		LobbyUI->InitializeHUD();
	}
}