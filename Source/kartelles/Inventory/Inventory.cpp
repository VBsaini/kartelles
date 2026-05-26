// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "kartelles/Structure/GenericStructs.h"


// Sets default values
AInventory::AInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();
	GridWidth = 8.0;
	GridHeight = 6.0;
	CellSize = 64;
	int cells = (GridWidth * GridHeight) - 1;
	for (int i = 0; i < cells; i++) {
		FInventoryCell cell;
		cell.Occupied = false;
		cell.ItemId = -1;
		InventoryCells.Add(cell);
	}
	
}

// Called every frame
void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AInventory::GetCellIndex(int32 X, int32 Y)
{
	int32 index = (Y * GridWidth) + X;
	return index;
}

void AInventory::PlaceItem(int32 StartX, int32 StartY, FItemDataStruct ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	for(const FIntPoint& offset : ItemData.ShapeOffsets) {
		int32 cellX = StartX + offset.X;
		int32 cellY = StartY + offset.Y;
		int32 cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			InventoryCells[cellIndex].Occupied = true;
			InventoryCells[cellIndex].ItemId = ItemData.ItemID;
		}
	}
}

void AInventory::RemoveItem(int32 StartX, int32 StartY, FItemDataStruct ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	for(const FIntPoint& offset : ItemData.ShapeOffsets) {
		int32 cellX = StartX + offset.X;
		int32 cellY = StartY + offset.Y;
		int32 cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			InventoryCells[cellIndex].Occupied = false;
			InventoryCells[cellIndex].ItemId = -1;
		}
	}
}

bool AInventory::CanPlaceItem(int32 StartX, int32 StartY, FItemDataStruct ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	for(const FIntPoint& offset : ItemData.ShapeOffsets) {
		int32 cellX = StartX + offset.X;
		int32 cellY = StartY + offset.Y;
		if(cellY < 0 || cellY >= GridHeight || cellX < 0 || cellX >= GridWidth) {
			return false; // Out of bounds
		}
		int32 cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			if(InventoryCells[cellIndex].Occupied) {
				return false;
			}
		} else {
			return false; // Out of bounds
		}
	}
	return true;
}
