// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemPlacementRule.generated.h"

struct FItemData;
class AInventory;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KARTELLES_API UItemPlacementRule : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	AInventory* InvRef = nullptr;




public:
	UFUNCTION(BlueprintNativeEvent)
	bool CanPlace(int32 startX, int32 startY, FItemData item);


};
