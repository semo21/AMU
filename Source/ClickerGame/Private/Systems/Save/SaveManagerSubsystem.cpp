// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Economy/Data/ClickerEconomySnapshot.h"
#include "Systems/Economy/Data/GlobalEconomySnapshot.h"
#include "Systems/Progress/Data/GlobalProgressSnapshot.h"
#include "Systems/Save/Data/PlayerSaveGame.h"

#include "Kismet/GameplayStatics.h"

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
		SaveGameObject = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	
	if(!SaveGameObject){
		SaveGameObject = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	}
}

void USaveManagerSubsystem::SaveProgress(const FClickerEconomySnapshot& S) {
	FClickerEconomySnapshot Stamped = S;
	Stamped.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

	SaveGameObject->LevelSnapshots.Add(TEXT("Clicker"), FInstancedStruct::Make<FClickerEconomySnapshot>(Stamped));
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FClickerEconomySnapshot& Out) {
	const FInstancedStruct* Found = SaveGameObject->LevelSnapshots.Find(TEXT("Clicker"));
	if (!Found) return false;

	const FClickerEconomySnapshot* Snapshot = Found->GetPtr<FClickerEconomySnapshot>();
	if (!Snapshot) return false;

	Out = *Snapshot;
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