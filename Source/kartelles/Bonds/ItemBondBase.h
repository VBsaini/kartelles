// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemBondBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KARTELLES_API UItemBondBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ActivateBondEffect();


	UFUNCTION(BlueprintNativeEvent)
	void DeactivateBondEffect();
	
};
