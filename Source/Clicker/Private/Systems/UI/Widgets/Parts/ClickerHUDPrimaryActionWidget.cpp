// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDPrimaryActionWidget.h"

#include "Components/Button.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Player/ClickerPlayerController.h"
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidget.h"

void UClickerHUDPrimaryActionWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AClickerPlayerController* InPC){
	Super::InitializePart_Implementation(InUI, InPC);
	if (Btn_Upgrade && UpgradeActionTag.IsValid()) {
		Btn_Upgrade->InitializeButton(InPC, InUI->GetActionButtonRegistry(), UpgradeActionTag);
	}
	if (Btn_Boost && BoostActionTag.IsValid()) {
		Btn_Boost->InitializeButton(InPC, InUI->GetActionButtonRegistry(), BoostActionTag);
	}
	if (Btn_Exchange && ExchangeActionTag.IsValid()) {
		Btn_Exchange->InitializeButton(InPC, InUI->GetActionButtonRegistry(), ExchangeActionTag);
	}
}