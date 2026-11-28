// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/ClickerPlayerController.h"

#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Actors/Clicker/ClickerTarget.h"

void AClickerPlayerController::BeginPlay() {
	Super::BeginPlay();

	ClickerEconomySubsystemRef = GetWorld()->GetSubsystem<UClickerEconomySubsystem>();
	ClickerUISubsystemRef = GetWorld()->GetSubsystem<UClickerUISubsystem>();
	check(ClickerEconomySubsystemRef && ClickerUISubsystemRef);
}

// private field
void AClickerPlayerController::OnClick() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	auto* Target = Cast<AClickerTarget>(HitResult.GetActor());
	if (!HitResult.bBlockingHit || !Target) return;

	const double Earned = ClickerEconomySubsystemRef->OnClicked();
	Target->HandleClicked(HitResult.Location);
	ClickerUISubsystemRef->ShowFloatingText(FString::Printf(TEXT("%f"), Earned), HitResult.Location);
}

void AClickerPlayerController::OnUpgradeClicked() {
	ClickerEconomySubsystemRef->TryUpgrade();
}

void AClickerPlayerController::OnBoostClicked() {
	UE_LOG(LogTemp, Warning, TEXT("Boost button clicked - this is a placeholder action"));

}

void AClickerPlayerController::OnExchangeClicked() {
	UE_LOG(LogTemp, Warning, TEXT("Exchange button clicked - this is a placeholder action"));
	ClickerEconomySubsystemRef->TryExchange();
}


void AClickerPlayerController::OnSaveClicked() {
	ClickerEconomySubsystemRef->RequestSave();
	UE_LOG(LogTemp, Warning, TEXT("Save button clicked - this is a placeholder action"));
}

void AClickerPlayerController::OnLoadClicked() {
	ClickerEconomySubsystemRef->RequestLoad();
	UE_LOG(LogTemp, Warning, TEXT("Load button clicked - this is a placeholder action"));
}

void AClickerPlayerController::HandleActionButtonClicked(const FGameplayTag& ActionTag) {
	if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Upgrade"))) {
		OnUpgradeClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Boost"))) {
		OnBoostClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Exchange"))) {
		OnExchangeClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Save"))) {
		OnSaveClicked();
	}
	else if (ActionTag.MatchesTagExact(FGameplayTag::RequestGameplayTag("UI.Action.Load"))) {
		OnLoadClicked();
	}
}

void AClickerPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (IsLocalController()) {
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AClickerPlayerController::OnClick);
	}
}