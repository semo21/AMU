// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"

void UGlobalEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	SaveManagerRef = Collection.InitializeDependency<USaveManagerSubsystem>();
	check(SaveManagerRef);

	SaveManagerRef->LoadProgress(GlobalEconomySnapshot);
}
void UGlobalEconomySubsystem::Deinitialize() {
	SaveManagerRef->SaveProgress(GlobalEconomySnapshot);

	Super::Deinitialize();
}

void UGlobalEconomySubsystem::AddGlobalCurrency(double Amount) {
	GlobalEconomySnapshot.GlobalCurrency += Amount;
	SaveManagerRef->SaveProgress(GlobalEconomySnapshot);
}

bool UGlobalEconomySubsystem::TrySpendGlobalCurrency(double Amount) {
	if (Amount <= 0.0) {
		UE_LOG(LogTemp, Warning, TEXT("GlobalEconomySubsystem::TrySpendGlobalCurrency / Price is wrong"));
		return false;
	}

	if (GlobalEconomySnapshot.GlobalCurrency < Amount) {
		UE_LOG(LogTemp, Warning, TEXT("GlobalEconomySubsystem::TrySpendGlobalCurrency / Need more global currency"));
		return false;
	}

	GlobalEconomySnapshot.GlobalCurrency -= Amount;
	SaveManagerRef->SaveProgress(GlobalEconomySnapshot);
	UE_LOG(LogTemp, Warning, TEXT("Spending global currency successfully, global currecy: %.2f"), GlobalEconomySnapshot.GlobalCurrency);
	return true;
}