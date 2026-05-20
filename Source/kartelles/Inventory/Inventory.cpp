// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "kartelles/Inventory/Structure/ItemDataStruct.cpp"


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
	for (const FVector2D& Offset : ItemData.ShapeOffsets) 
	{
		float X = StartX + Offset.X;
		float Y = StartY + Offset.Y;
		GetCellIndex(X, Y);
		// Set Grid Item
	}

}

