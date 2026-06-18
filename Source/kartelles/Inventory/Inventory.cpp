// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "kartelles/Bonds/ItemBondBase.h"
#include "Engine/DataTable.h"
#include "kartelles/Private/UserCharacter.h"
#include "kartelles/Inventory/PlacementRule/ItemPlacementRule.h"

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
	BondCount = {};
	// get player
	PlayerRef = Cast<AUserCharacter>(GetOwner());
	int cells = (GridWidth * GridHeight);
	for (int i = 0; i < cells; i++) {
		FInventoryCell cell;
		cell.Occupied = false;
		cell.ItemId = -1;
		InventoryCells.Add(cell);
	}
	
}


int32 AInventory::GetCellIndex(int32 X, int32 Y)
{
	int32 index = (Y * GridWidth) + X;
	return index;
}

void AInventory::PlaceItem(int32 StartX, int32 StartY, FItemData ItemData, UDataTable* BondTable)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	BondCount.FindOrAdd(ItemData.Bond) += ItemData.BondContribution;
	for(const FIntPoint& offset : ItemData.ShapeOffsets) {
		int32 cellX = StartX + offset.X;
		int32 cellY = StartY + offset.Y;
		int32 cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			InventoryCells[cellIndex].Occupied = true;
			InventoryCells[cellIndex].ItemId = ItemData.ItemID;
		}
	}
	InventoryItemData.Add(GetCellIndex(StartY, StartX), ItemData);
	ApplyEffects(BondTable);
}

void AInventory::RemoveItem(int32 StartX, int32 StartY, FItemData ItemData)
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

bool AInventory::CanPlaceItem(int32 StartX, int32 StartY, FItemData ItemData)
{
	int itemWidth = ItemData.Width;
	int itemHeight = ItemData.Height;
	UItemPlacementRule* Rule = nullptr;
	if (ItemData.PlacementRule) {
		Rule = NewObject<UItemPlacementRule>(this, ItemData.PlacementRule);
	}
	for(const FIntPoint& offset : ItemData.ShapeOffsets) {
		int32 cellX = StartX + offset.X;
		int32 cellY = StartY + offset.Y;
		if(cellY < 0 || cellY >= GridHeight || cellX < 0 || cellX >= GridWidth) {
			return false; // Out of bounds
		}
		int32 cellIndex = GetCellIndex(cellX, cellY);
		if(InventoryCells.IsValidIndex(cellIndex)) {
			if (!ItemData.SubItem) {
				if (InventoryCells[cellIndex].Occupied) {
					return false;
				}
			}
			else {
				if (!InventoryCells[cellIndex].Occupied) {
					return false;
				}
			}
		} else {
			return false; // Out of bounds
		}
		if (ItemData.PlacementRule) {
			if (Rule) {
				Rule->InvRef = this;
				if(!Rule->CanPlace(cellX, cellY, ItemData)) {
					return false;
				}
			}
		}
	}


	return true;
}

void AInventory::ApplyEffects(UDataTable* BondTable)
{
	if (BondTable) {
		UE_LOG(LogTemp, Warning, TEXT("Appy Effects C++"))
		static const FString ContextString(TEXT("Iterating Data Table"));
		TArray<FBondEffect* > Rows;
		BondTable->GetAllRows<FBondEffect>(ContextString, Rows);
		for (auto& Row : Rows)
		{
			int32 Count = BondCount.FindRef(Row->BondName);

			FGameplayTag EffectTag = Row->EffectTag;
			if (Count >= Row->ItemRequired)
			{
				if (!ActiveBondEffects.Contains(EffectTag))
				{
					// activate
					/*UItemBondBase* Effect = NewObject<UItemBondBase>(this, Row->Effect);
					if (Effect)
					{
						Effect->ActivateBondEffect();
					}*/
					PlayerRef->AddAbilityTag(Row->EffectTag);
					ActiveBondEffects.Add(EffectTag);
				}
			}
			else
			{
				if(ActiveBondEffects.Contains(EffectTag))
				{
					/*UItemBondBase* Effect = ActiveBondEffects[EffectTag];
					if (Effect)
					{
						Effect->DeactivateBondEffect();
					}*/
					PlayerRef->RemoveAbilityTag(Row->EffectTag);
					ActiveBondEffects.Remove(EffectTag);
				}
			}
		}
	}
}

bool AInventory::IsCellOccupied(int32 X, int32 Y)
{
	return false;
}

int32 AInventory::GetCellItemId(int32 X, int32 Y)
{
	int32 index = GetCellIndex(X, Y);
	int32 id = -1;
	if (InventoryCells.IsValidIndex(index)) {
		id = InventoryCells[index].ItemId;
	}
	return id;
}

FItemData AInventory::GetItemAt(int32 X, int32 Y)
{	

	return InventoryItemData[GetCellIndex(X, Y)];
}

TSet<FItemData> AInventory::GetAdjacentItems(int32 X, int32 Y)
{
	TSet<FItemData> AdjacentItems;
	FItemData CurrentItem = GetItemAt(X, Y);
	static const FIntPoint Directions[4] = {
		FIntPoint(-1, 0), FIntPoint(1, 0), FIntPoint(0, -1), FIntPoint(0, 1)
	};
	for (auto& offset : CurrentItem.ShapeOffsets) {
		for (auto& direction : Directions) {
			int32 cellX = X + offset.X + direction.X;
			int32 cellY = Y + offset.Y + direction.Y;
			if (cellY < 0 || cellY >= GridHeight || cellX < 0 || cellX >= GridWidth) {
				continue; // Out of bounds
			}
			int32 cellIndex = GetCellIndex(cellX, cellY);
			if (InventoryCells.IsValidIndex(cellIndex)) {
				if (InventoryCells[cellIndex].Occupied) {
					FItemData item = GetItemAt(cellX, cellY);
					if (item.ItemID != CurrentItem.ItemID) {
						AdjacentItems.Add(item);
					}
				}
			}
		}
	}
	return AdjacentItems;
}
