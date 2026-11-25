// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDStatsWidget.h"

#include "Components/TextBlock.h"

void UClickerHUDStatsWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AClickerPlayerController* InPC) {
	Super::InitializePart_Implementation(InUI, InPC);
}

void UClickerHUDStatsWidget::OnEconomyChangedUI_Implementation(const FClickerEconomyStats& Stats) {
	Super::OnEconomyChangedUI_Implementation(Stats);
	Txt_Value_Currency->SetText(FText::AsNumber(Stats.Currency));
	Txt_Value_CPC->SetText(FText::AsNumber(Stats.CurrencyPerClick));
	Txt_Value_UpgradeCost->SetText(FText::AsNumber(Stats.UpgradeCost));

	Txt_Value_CPS->SetText(FText::AsNumber(Stats.CurrencyPerSecond));
}