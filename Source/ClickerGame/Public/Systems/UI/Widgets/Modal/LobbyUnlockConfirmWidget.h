// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUnlockConfirmWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnlockConfirmed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnlockCancelled);
/**
 * 
 */
UCLASS(Abstract)
class CLICKERGAME_API ULobbyUnlockConfirmWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetUnlockInfo(const FText& LevelName, double Price, double Balance);

	UPROPERTY(BlueprintAssignable, Category="Unlock")
	FOnUnlockConfirmed OnConfirmed;
	UPROPERTY(BlueprintAssignable, Category = "Unlock")
	FOnUnlockCancelled OnCancelled;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_LevelName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Price;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Txt_Balance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Confirm;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Cancel;

private:
	UFUNCTION() 
	void HandleConfirmClicked();
	UFUNCTION() 
	void HandleCancelClicked();
};
