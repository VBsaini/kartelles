// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerSubsystem.h"

#include "kartelles/Private/UserCharacter.h"
#include "AbilitySystemComponent.h"
#include "Math/UnrealMathUtility.h"

AActor* UEnemyManagerSubsystem::GetNearestEnemy(FVector origin, float MaxRadius, FGameplayTag SearchTag)
{
	AActor* BestTarget = nullptr;
	float  BestDistsq = MaxRadius * MaxRadius;

	for(int32 i = ActiveEnemies.Num() - 1; i >= 0; i--)
	{
		AUserCharacter* Enemy = ActiveEnemies[i].Get();
		if(!Enemy)
		{
			ActiveEnemies.RemoveAt(i);
			continue;
		}
		if(Enemy->GetAbilitySystemComponent()->HasMatchingGameplayTag(SearchTag))
		{
			float Distsq = FVector::DistSquared(origin, Enemy->GetActorLocation());
			if(Distsq < BestDistsq)
			{
				BestDistsq = Distsq;
				BestTarget = Enemy;
			}
		}
	}
	return BestTarget;
}
