// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UserCharacter.generated.h"


class UInputAction;
class UBasicAttributeSet;


UCLASS()
class AUserCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UBasicAttributeSet> BasicAttributeSet;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

public:
	// Sets default values for this character's properties
	AUserCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Ability System Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;



};
