// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_DamagePlayerCalc.generated.h"

/**
 * 
 */
UCLASS()
class KARTELLES_API UGE_DamagePlayerCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGE_DamagePlayerCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
	// The Gameplay Effect class we will use to deal the reflected damage back to the attacker
	UPROPERTY(EditDefaultsOnly, Category = "Reflection")
	TSubclassOf<class UGameplayEffect> ReflectionEffectClass;

	// The Set By Caller tag used to pass in our base damage
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTag DamageTag;
};
