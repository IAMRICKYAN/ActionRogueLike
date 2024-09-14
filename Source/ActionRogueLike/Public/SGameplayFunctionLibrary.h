// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable,Category="GamePlay")
	static bool ApplyDamage(AActor* DamageCauser,AActor* TargetActor,int DamageAmount);

	UFUNCTION(BlueprintCallable,Category="GamePlay")
	static bool ApplyDirctionalDamage(AActor* DamageCauser,AActor* TargetActor,int DamageAmount,const FHitResult& HitResult);
	
};
