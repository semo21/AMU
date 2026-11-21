// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalHUDRootWidgetBase.generated.h"

class UOverlay;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CLICKERGAME_API UGlobalHUDRootWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowModal(UUserWidget* ModalWidget);
	void ClearModal();

protected:
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UPanelWidget> ToastLayer;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UPanelWidget> FloatingLayer;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UOverlay> ModalLayer;

};
