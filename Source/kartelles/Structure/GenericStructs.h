// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/Texture2D.h"
#include "kartelles/Bonds/ItemBondBase.h"
#include "kartelles/Inventory/PlacementRule/ItemPlacementRule.h"
#include "GenericStructs.generated.h"



// ========= Inventory Cell
USTRUCT(BlueprintType)
struct FInventoryCell {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool Occupied;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemId;
};

// ========= Bond Effect
USTRUCT(BlueprintType)
struct FBondEffect : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	int32 BondId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	FName BondName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	int32 ItemRequired;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	TSubclassOf<UItemBondBase> Effect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	FGameplayTag EffectTag;
};



// ========= Item Data
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Width = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Height = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bRotatable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ItemPrice = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FIntPoint> ShapeOffsets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayAbility> ItemAbilityClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	//FGameplayAbilitySpecHandle ItemAbilityHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FGameplayTag ItemTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	FName Bond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond")
	int32 BondContribution = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Placement")
	TSubclassOf<class UItemPlacementRule> PlacementRule;
};