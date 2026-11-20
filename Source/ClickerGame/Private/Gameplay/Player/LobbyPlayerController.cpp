// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/LobbyPlayerController.h"
#include "Systems/UI/LobbyUISubsystem.h"

void ALobbyPlayerController::RequestLevelUnlock(const FGameplayTag& LevelTag) {
	GetWorld()->GetSubsystem<ULobbyUISubsystem>()->ShowUnlockConfirm(LevelTag);
}