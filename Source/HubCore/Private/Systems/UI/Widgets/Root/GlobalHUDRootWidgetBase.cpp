// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Root/GlobalHUDRootWidgetBase.h"

#include "Components/PanelWidget.h"
#include "Components/OverlaySlot.h"
#include "Components/Overlay.h"

void UGlobalHUDRootWidgetBase::ShowModal(UUserWidget* ModalWidget) {
	if (!ensure(ModalLayer)) return;

	ModalLayer->ClearChildren();
	if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(ModalLayer->AddChild(ModalWidget))) {
		OverlaySlot->SetHorizontalAlignment(HAlign_Center);
		OverlaySlot->SetVerticalAlignment(VAlign_Center);
	}
}

void UGlobalHUDRootWidgetBase::ClearModal() {
	if (!ensure(ModalLayer)) return;
	ModalLayer->ClearChildren();
}