// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GameplayTagContainer.h"

#include "LevelRegistrySubsystem.generated.h"


class ULevelRegistry;
class ULevelDefinition;

/**
 *
 */
UCLASS(Config = Game, DefaultConfig)
class HUBCORE_API ULevelRegistrySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const ULevelDefinition* FindLevelDefinition(const FGameplayTag& LevelTag) const;

private:
	UPROPERTY(Config)
	TSoftObjectPtr<ULevelRegistry> LevelRegistryAsset;

	UPROPERTY(Transient)
	TObjectPtr<ULevelRegistry> LevelRegistry;

	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<ULevelDefinition>> DefinitionsByTag;
};