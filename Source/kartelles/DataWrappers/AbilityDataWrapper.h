// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "kartelles/Structure/GenericStructs.h"

#include "AbilityDataWrapper.generated.h"



/**
 * 
 */
UCLASS(Blueprintable)
class KARTELLES_API UAbilityDataWrapper : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	int32 IndexX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	int32 IndexY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	FItemData ItemData;
	
};
