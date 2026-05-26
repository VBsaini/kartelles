// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/Texture2D.h"
#include "GenericStructs.generated.h"

USTRUCT(BlueprintType)
struct FItemDataStruct : public FTableRowBase
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
	TArray<FIntPoint> ShapeOffsets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UGameplayAbility> ItemAbilityClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	//FGameplayAbilitySpecHandle ItemAbilityHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FGameplayTag ItemTags;
};

USTRUCT(BlueprintType)
struct FInventoryCell {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool Occupied;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemId;
};
