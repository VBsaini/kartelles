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

float AInventory::GetCellIndex(float X, float Y)
{
	float index = (Y * GridWidth) + X;
	return index;
}

void AInventory::PlaceItem(float StartX, float StartY, FItemDataStruct ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	for(const FVector2D& offset : ItemData.ShapeOffsets) {
		float cellX = StartX + offset.X;
		float cellY = StartY + offset.Y;
		float cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			InventoryCells[cellIndex].Occupied = true;
			InventoryCells[cellIndex].ItemId = ItemData.ItemID;
		}
	}
}

void AInventory::RemoveItem(float StartX, float StartY, FItemDataStruct ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	for(const FVector2D& offset : ItemData.ShapeOffsets) {
		float cellX = StartX + offset.X;
		float cellY = StartY + offset.Y;
		float cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			InventoryCells[cellIndex].Occupied = false;
			InventoryCells[cellIndex].ItemId = -1;
		}
	}
}

bool AInventory::CanPlaceItem(float StartX, float StartY, FItemDataStruct ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	for(const FVector2D& offset : ItemData.ShapeOffsets) {
		float cellX = StartX + offset.X;
		float cellY = StartY + offset.Y;
		if(cellY < 0 || cellY >= GridHeight || cellX < 0 || cellX >= GridWidth) {
			return false; // Out of bounds
		}
		float cellIndex = GetCellIndex(cellX, cellY);
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
