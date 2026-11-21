// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/UI/Widgets/Root/GlobalHUDRootWidgetBase.h"

#include "LobbyHUDRootWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class LOBBY_API ULobbyHUDRootWidget : public UGlobalHUDRootWidgetBase
{
	GENERATED_BODY()
	
public:
	void SetGlobalCurrency(double Amount);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_GlobalCurrency;
};
