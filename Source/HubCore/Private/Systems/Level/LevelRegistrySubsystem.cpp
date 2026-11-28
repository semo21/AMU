// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Level/LevelRegistrySubsystem.h"

#include "Systems/Level/Data/LevelRegistry.h"
#include "Systems/Level/Data/LevelDefinition.h"

void ULevelRegistrySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	LevelRegistry = LevelRegistryAsset.LoadSynchronous();
	checkf(LevelRegistry, TEXT("ULevelRegistrySubsystem::Initialize / LevelRegistry is not loaded"));

	for (ULevelDefinition* Definition : LevelRegistry->Levels) {
		checkf(Definition, TEXT("ULevelRegistrySubsystem::Initialize / Empty slot in LevelRegistry"));
		checkf(!DefinitionsByTag.Contains(Definition->LevelTag), TEXT("ULevelRegistrySubsystem::Initialize / Duplicate level tag: %s"), *Definition->LevelTag.ToString());
		DefinitionsByTag.Add(Definition->LevelTag, Definition);
		UE_LOG(LogTemp, Log, TEXT("ULevelRegistrySubsystem::Initialize / Add tag: %s"), *Definition->LevelTag.ToString());
	}
}

const ULevelDefinition* ULevelRegistrySubsystem::FindLevelDefinition(const FGameplayTag& LevelTag) const {
	const TObjectPtr<ULevelDefinition>* Found = DefinitionsByTag.Find(LevelTag);
	return Found ? Found->Get() : nullptr;
}
