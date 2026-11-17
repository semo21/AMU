// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SaveManagerSubsystem.generated.h"

struct FClickerEconomySnapshot;
struct FGlobalEconomySnapshot;
struct FGlobalProgressSnapshot;
class UPlayerSaveGame;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void SaveProgress(const FClickerEconomySnapshot& Snapshot);	
	bool LoadProgress(FClickerEconomySnapshot& OutSnapshot);

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
