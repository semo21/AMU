// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"

#include "ClickerPlayerController.generated.h"

class UClickerEconomySubsystem;
class UClickerUISubsystem;
/**
 *
 */
UCLASS()
class CLICKER_API AClickerPlayerController : public AMyPlayerControllerBase
{
	GENERATED_BODY()
public:
	UFUNCTION()	void OnClick();
	UFUNCTION()	void OnUpgradeClicked();
	UFUNCTION() void OnBoostClicked();
	UFUNCTION() void OnTestClicked();
	UFUNCTION()	void OnSaveClicked();
	UFUNCTION()	void OnLoadClicked();
	virtual void HandleActionButtonClicked(const FGameplayTag& ActionTag) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	

private:
	UPROPERTY()
	TObjectPtr<UClickerEconomySubsystem> ClickerEconomySubsystemRef;

	UPROPERTY()
	TObjectPtr<UClickerUISubsystem> ClickerUISubsystemRef;
};
