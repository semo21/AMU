// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/MyWorldSubsystemBase.h"
#include "Systems/Economy/Data/GlobalEconomySnapshot.h"

#include "GameplayTagContainer.h"
#include "LobbyUISubsystem.generated.h"

class ULobbyHUDRootWidget;
class ULobbyUnlockConfirmWidget;
class ULobbyUISettings;
/**
 *
 */
UCLASS(Config = Game, DefaultConfig)
class HUBCORE_API ULobbyUISubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void InitializeHUD();
	void ShowUnlockConfirm(const FGameplayTag& LevelTag);

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;

private:
	UFUNCTION()
	void HandleGlobalEconomyChanged(const FGlobalEconomySnapshot& Snapshot);
	UFUNCTION()
	void HandleUnlockConfirmed();
	UFUNCTION()
	void HandleUnlockCancelled();

	UPROPERTY(Config)
	TSoftObjectPtr<ULobbyUISettings> UISettingsAsset;
	UPROPERTY(Transient)
	TObjectPtr<ULobbyUISettings> UISettings;
	UPROPERTY()
	TObjectPtr<ULobbyHUDRootWidget> LobbyRoot;
	UPROPERTY()
	TObjectPtr<ULobbyUnlockConfirmWidget> UnlockConfirmWidget;
	FGameplayTag PendingUnlockLevel;
};
