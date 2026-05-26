// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"
struct FItemDataStruct;
struct FInventoryCell;
UCLASS()
class KARTELLES_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventory();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float GridWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float GridHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryCell> InventoryCells;
	//TSub

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetCellIndex(int32 X, int32 Y);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PlaceItem(int32 StartX, int32 StartY, FItemDataStruct ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(int32 StartX, int32 StartY, FItemDataStruct ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanPlaceItem(int32 StartX, int32 StartY, FItemDataStruct ItemData);
};
