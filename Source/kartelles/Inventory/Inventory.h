// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "kartelles/Structure/GenericStructs.h"
#include "Inventory.generated.h"

struct FInventoryCell;
class UDataTable;
class UItemBondBase;
class AUserCharacter;

UCLASS()
class KARTELLES_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:
	AInventory();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	AUserCharacter* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonds")
	TMap<FName, int32> BondCount;
	
	UPROPERTY(BlueprintReadOnly, Category = "Bonds")
	TSet<FGameplayTag> ActiveBondEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float GridWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float GridHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryCell> InventoryCells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<int32, FItemData> InventoryItemData;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetCellIndex(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PlaceItem(int32 StartX, int32 StartY, FItemData ItemData, UDataTable* BondTable);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(int32 StartX, int32 StartY, FItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanPlaceItem(int32 StartX, int32 StartY, FItemData ItemData);

	UFUNCTION(BlueprintCallable, Category = "Bonds")
	void ApplyEffects(UDataTable* BondTable);

	UFUNCTION(BlueprintCallable)
	bool IsCellOccupied(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable)
	int32 GetCellItemId(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable)
	FItemData GetItemAt(int32 X, int32 Y);

	TSet<FItemData> GetAdjacentItems(int32 X, int32 Y);
};
