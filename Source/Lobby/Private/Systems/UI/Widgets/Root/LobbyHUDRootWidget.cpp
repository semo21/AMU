// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Root/LobbyHUDRootWidget.h"
#include "Components/TextBlock.h"

void ULobbyHUDRootWidget::SetGlobalCurrency(double Amount) {
	if (Txt_GlobalCurrency) {
		Txt_GlobalCurrency->SetText(FText::AsNumber(Amount));
	}
}