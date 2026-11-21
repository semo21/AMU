// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SaveManagerSubsystem.generated.h"

struct FGlobalEconomySnapshot;
struct FGlobalProgressSnapshot;

struct FGameplayTag;
struct FInstancedStruct;
class UPlayerSaveGame;
/**
 * 
 */
UCLASS()
class HUBCORE_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void SaveLevelSnapshot(const FGameplayTag& LevelTag, const FInstancedStruct& Snapshot);
	bool LoadLevelSnapshot(const FGameplayTag& LevelTag, FInstancedStruct& OutSnapshot) const;

	void SaveProgress(const FGlobalEconomySnapshot& Snapshot);
	bool LoadProgress(FGlobalEconomySnapshot& OutSnapshot);

	void SaveProgress(const FGlobalProgressSnapshot& Snapshot);
	bool LoadProgress(FGlobalProgressSnapshot& OutSnapshot);

protected:
	
	
private:
	UPROPERTY()
	TObjectPtr<UPlayerSaveGame> SaveGameObject;

	const FString SaveSlotName = TEXT("ClickerSaveSlot");
	const int32 UserIndex = 0;
};
