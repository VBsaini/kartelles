// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class KARTELLES_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:

	UBasicAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Shield)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxShield)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Gold)

};