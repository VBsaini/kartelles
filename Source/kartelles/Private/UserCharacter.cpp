// Fill out your copyright notice in the Description page of Project Settings.


#include "UserCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "kartelles/DataWrappers/AbilityDataWrapper.h"
#include "kartelles/Structure/GenericStructs.h"

// Abilities
#include "AbilitySystemComponent.h"
#include "kartelles/GAS/Attributes/BasicAttributeSet.h"
#include "kartelles/GAS/Attributes/DamageAttributeSet.h"

#include "kartelles/Manager/EnemyManagerSubsystem.h"

// Sets default values
AUserCharacter::AUserCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	// Add the basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));
	DamageAttributeSet = CreateDefaultSubobject<UDamageAttributeSet>(TEXT("DamageAttributeSet"));

}

// Called when the game starts or when spawned
void AUserCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if(AbilitySystemComponent) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	if (GetWorld() && GetWorld()->IsGameWorld()) {
		UEnemyManagerSubsystem* EnemyManager = GetWorld()->GetSubsystem<UEnemyManagerSubsystem>();
		if (EnemyManager) {
			EnemyManager->RegisterEnemy(this);
		}
	}

}

//void AUserCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	if (GetWorld())
//	{
//		UEnemyManagerSubsystem* EnemyManager = GetWorld()->GetSubsystem<UEnemyManagerSubsystem>();
//		if (EnemyManager) 
//		{
//			EnemyManager->UnregisterEnemy(this);
//		}
//	}
//	Super::EndPlay(EndPlayReason);
//}


// Called every frame
void AUserCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUserCharacter::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

// Called to bind functionality to input
void AUserCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUserCharacter::Move);
	}
}

UAbilitySystemComponent* AUserCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUserCharacter::AddAbilityTag(FGameplayTag Tag)
{
	ActiveTags.AddTag(Tag);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTag(Tag);
	}
}

void AUserCharacter::RemoveAbilityTag(FGameplayTag Tag)
{
	ActiveTags.RemoveTag(Tag);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
	}
}

void AUserCharacter::AddAbility(FItemData item, int32 X, int32 Y)
{
	FGameplayAbilitySpec spec = FGameplayAbilitySpec(item.ItemAbilityClass, 0, 0);
	UAbilityDataWrapper* DataWrapper = NewObject<UAbilityDataWrapper>(this);
	DataWrapper->ItemData = item; // Store the item data in the wrapper for later retrieval in the ability
	DataWrapper->IndexX = X; // Store the index in the wrapper for later retrieval in the ability
	DataWrapper->IndexY = Y; // Store the index in the wrapper for later retrieval in the ability
	spec.SourceObject = DataWrapper; // Store the item data in the SourceObject of the spec for later retrieval in the ability

	AbilitySystemComponent->GiveAbility(spec);
}
