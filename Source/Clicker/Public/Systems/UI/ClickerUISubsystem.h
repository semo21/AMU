// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/MyWorldSubsystemBase.h"
#include "GameplayTagContainer.h"
#include "Systems/Economy/Data/ClickerEconomyStats.h"

#include "ClickerUISubsystem.generated.h"

class USoundBase;				class UUserWidget; 
class UButton;					class UTextBlock; 

class UClickerEconomySubsystem; class AClickerPlayerController;
class UClickFloatingTextWidget; class UIdleRewardTextWidget;
class UClickerUISettings;		class UToastWidgetBase;			
class UActionButtonRegistry;	

struct FActionButtonDefinition;

// Economy changed event for UI, passes the new stats to update displays
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChangedUI, const FClickerEconomyStats&, Stats);

UCLASS(Config=Game, DefaultConfig)
class CLICKER_API UClickerUISubsystem : public UMyWorldSubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void InitializeHUDRoot(AClickerPlayerController* PC);
	void BindEconomySubsystem(UClickerEconomySubsystem* Eco);
	void ShowFloatingText(const FString& Message, const FVector& WorldLocation);
	void ShowReward(double Amount, bool bIsOffline);
	const UActionButtonRegistry* GetActionButtonRegistry() const { return ActionButtonRegistry; }
	UFUNCTION()	
	void OnEconomyChanged(const FClickerEconomyStats& Stats);
	UFUNCTION() 
	void OnPassiveIncome(double AmountPerSec);
	UFUNCTION(BlueprintCallable, Category="UI|Economy")
	const FClickerEconomyStats& GetCachedClickerEconomyStats() const { return CachedClickerEconomyStats; }

	UPROPERTY(BlueprintAssignable, Category="UI|Events")
	FOnEconomyChangedUI OnEconomyChangedUI;
	UPROPERTY(Config, EditAnywhere, Category="Settings")	
	TSoftObjectPtr<UClickerUISettings> UISettingsAsset;
	UPROPERTY(Config, EditAnywhere, Category="Settings")
	TSoftObjectPtr<UActionButtonRegistry> ActionButtonRegistryAsset = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<UActionButtonRegistry> ActionButtonRegistry = nullptr;
	UPROPERTY()	
	USoundBase* OfflineRewardSound = nullptr;
	

protected:
	virtual TSubclassOf<AGameModeBase> GetRequiredGameModeClass() const override;
	UToastWidgetBase* GetWidgetFromPool(TArray<UToastWidgetBase*>& Pool, TSubclassOf<UToastWidgetBase> ToastWidgetClass);

	UPROPERTY() 
	TArray<UToastWidgetBase*> FloatingTextPool;
	UPROPERTY() 
	TArray<UToastWidgetBase*> RewardPool;
	UPROPERTY() 
	TSubclassOf<UToastWidgetBase> FloatingTextWidgetClass;
	UPROPERTY() 
	TSubclassOf<UToastWidgetBase> RewardToastClass;
	UPROPERTY() 
	TWeakObjectPtr<AClickerPlayerController> PlayerController;

private:
	void HandlePassiveIncome(double Amount);

	UPROPERTY(Transient) 
	FClickerEconomyStats CachedClickerEconomyStats;
	
	UPROPERTY()
	TObjectPtr<UClickerEconomySubsystem> EconomySubsystemRef = nullptr;
};
