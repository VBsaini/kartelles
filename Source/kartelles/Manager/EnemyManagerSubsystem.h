// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemyManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KARTELLES_API UEnemyManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemy(AUserCharacter* Enemy) { ActiveEnemies.AddUnique(Enemy); };

	UFUNCTION(BlueprintCallable)
	void UnregisterEnemy(AUserCharacter* Enemy) { ActiveEnemies.Remove(Enemy); };

	UFUNCTION(BlueprintCallable, Category="Combat")
	AActor* GetNearestEnemy(FVector origin, float MaxRadius, FGameplayTag SearchTag);
	
private:
	UPROPERTY()
	TArray<TWeakObjectPtr<AUserCharacter>> ActiveEnemies;
};
