// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelRegistry.generated.h"

class ULevelDefinition;
/**
 * 
 */
UCLASS()
class HUBCORE_API ULevelRegistry : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	TArray<TObjectPtr<ULevelDefinition>> Levels;
};
