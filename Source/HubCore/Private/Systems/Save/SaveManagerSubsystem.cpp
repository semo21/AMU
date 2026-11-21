// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Economy/Data/GlobalEconomySnapshot.h"
#include "Systems/Progress/Data/GlobalProgressSnapshot.h"
#include "Systems/Save/Data/PlayerSaveGame.h"

#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "InstancedStruct.h"

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
		SaveGameObject = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	
	if(!SaveGameObject){
		SaveGameObject = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	}
}

void USaveManagerSubsystem::SaveLevelSnapshot(const FGameplayTag& LevelTag, const FInstancedStruct& Snapshot) {
	SaveGameObject->LevelSnapshots.Add(LevelTag, Snapshot);
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadLevelSnapshot(const FGameplayTag& LevelTag, FInstancedStruct& OutSnapshot) const {
	const FInstancedStruct* Found = SaveGameObject->LevelSnapshots.Find(LevelTag);
	if (!Found) return false;

	OutSnapshot = *Found;
	return true;
}

void USaveManagerSubsystem::SaveProgress(const FGlobalEconomySnapshot& S) {
	SaveGameObject->GlobalEconomySnapshot = S;
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FGlobalEconomySnapshot& Out) {
		if (SaveGameObject) {
			Out = SaveGameObject->GlobalEconomySnapshot;
			return true;
		}
	
	return false;
}

void USaveManagerSubsystem::SaveProgress(const FGlobalProgressSnapshot& S) {
	SaveGameObject->GlobalProgressSnapshot = S;
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FGlobalProgressSnapshot& Out) {
		if (SaveGameObject) {
			Out = SaveGameObject->GlobalProgressSnapshot;
			return true;
		}
	return false;
}