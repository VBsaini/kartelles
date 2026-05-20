#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

USTRUCT(BlueprintType)
struct FInventoryCell
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Cell")
	bool Occupied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Cell")
	int32 ItemID;

};