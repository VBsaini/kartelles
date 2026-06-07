// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DamageAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class KARTELLES_API UDamageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UDamageAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, Attack)


	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData BaseAttack;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, BaseAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData CritRate;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, CritRate)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData CritDmg;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, CritDmg)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, FireRate)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData MeleeAttackSpeed;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, MeleeAttackSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageType;
	ATTRIBUTE_ACCESSORS_BASIC(UDamageAttributeSet, DamageType)
	
};
