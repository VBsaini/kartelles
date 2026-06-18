// Fill out your copyright notice in the Description page of Project Settings.


#include "./GE_DamagePlayerCalc.h"
#include "AbilitySystemComponent.h"
#include "kartelles/GAS/Attributes/BasicAttributeSet.h"

// -------------------------------------------------------------------------
// 1. Declare a static struct to handle capturing attributes safely
// -------------------------------------------------------------------------
struct FDamageStatics
{
	// Define the captures for Health and Shield
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Shield);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ReflectionMultiplier);

	FDamageStatics()
	{
		// Snapshot happens at creation, we capture from the Target
		// CHANGE 'UMyAttributeSet' to your actual class name!
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBasicAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBasicAttributeSet, Shield, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBasicAttributeSet, ReflectionMultiplier, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DStatics;
	return DStatics;
}

// -------------------------------------------------------------------------
// 2. Constructor: Tell the Exec Calc which attributes to capture
// -------------------------------------------------------------------------

UGE_DamagePlayerCalc::UGE_DamagePlayerCalc()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().ShieldDef);
	RelevantAttributesToCapture.Add(DamageStatics().ReflectionMultiplierDef);
}

void UGE_DamagePlayerCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (!TargetASC || !SourceASC) return;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Setup Evaluation Parameters
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Read the Initial Damage from Set By Caller
	float BaseDamage = Spec.GetSetByCallerMagnitude(DamageTag, false, 0.0f);
	if (BaseDamage <= 0.0f) return;

	// Capture the Target's Current Shield
	float CurrentShield = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ShieldDef, EvaluationParameters, CurrentShield);
	CurrentShield = FMath::Max(CurrentShield, 0.0f);

	// Capture the Target's Current Health
	float CurrentHealth = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, CurrentHealth);
	CurrentHealth = FMath::Max(CurrentHealth, 0.0f);

	// Capture the Target's Reflection Multipliet
	float ReflectionMultiplierNum = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ReflectionMultiplierDef, EvaluationParameters, ReflectionMultiplierNum);
	ReflectionMultiplierNum = FMath::Max(ReflectionMultiplierNum, 0.0f);

	// --- THE ROUTING MATH ---
	float ShieldDamage = FMath::Min(BaseDamage, CurrentShield);
	float SpilloverHealthDamage = BaseDamage - ShieldDamage;

	// Example: Reflect 20% of the ORIGINAL incoming damage
	float ReflectedDamage = BaseDamage * ReflectionMultiplierNum;

	// --- APPLY DAMAGE TO TARGET ---
	if (ShieldDamage > 0.0f)
	{
		// We use -ShieldDamage because additive operations require negative values to reduce stats
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().ShieldProperty, EGameplayModOp::Additive, -ShieldDamage));
	}

	if (SpilloverHealthDamage > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -SpilloverHealthDamage));
	}

	// --- APPLY REFLECTION TO ATTACKER ---
	// Make sure we have an effect assigned and we aren't reflecting damage to ourselves
	if (ReflectedDamage > 0.0f && ReflectionEffectClass && SourceASC != TargetASC)
	{
		FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
		ContextHandle.AddInstigator(TargetASC->GetAvatarActor(), TargetASC->GetAvatarActor());

		FGameplayEffectSpecHandle ReflectionSpecHandle = TargetASC->MakeOutgoingSpec(ReflectionEffectClass, 1.0f, ContextHandle);
		if (ReflectionSpecHandle.IsValid())
		{
			// Pass the reflected damage back using the exact same tag
			ReflectionSpecHandle.Data.Get()->SetSetByCallerMagnitude(DamageTag, ReflectedDamage);
			TargetASC->ApplyGameplayEffectSpecToTarget(*ReflectionSpecHandle.Data.Get(), SourceASC);
		}
	}
}
