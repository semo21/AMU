// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Modal/LobbyUnlockConfirmWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void ULobbyUnlockConfirmWidget::SetUnlockInfo(const FText& LevelName, double Price, double Balance) {

	Txt_LevelName->SetText(LevelName);
	Txt_Price->SetText(FText::AsNumber(Price));
	Txt_Balance->SetText(FText::AsNumber(Balance));

	Btn_Confirm->SetIsEnabled(Balance >= Price);
}

void ULobbyUnlockConfirmWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	Btn_Confirm->OnClicked.AddDynamic(this, &ULobbyUnlockConfirmWidget::HandleConfirmClicked);
	Btn_Cancel->OnClicked.AddDynamic(this, &ULobbyUnlockConfirmWidget::HandleCancelClicked);
}

void ULobbyUnlockConfirmWidget::HandleConfirmClicked() {
	OnConfirmed.Broadcast();
}

void ULobbyUnlockConfirmWidget::HandleCancelClicked() {
	OnCancelled.Broadcast();
}