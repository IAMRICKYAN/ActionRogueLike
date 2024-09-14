// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, int DamageAmount)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(TargetActor);
	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser,-DamageAmount);
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirctionalDamage(AActor* DamageCauser, AActor* TargetActor, int DamageAmount,
	const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser,TargetActor,DamageAmount))
	{

		UPrimitiveComponent* HitComp =  HitResult.GetComponent();
		if(HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.f,HitResult.ImpactPoint,HitResult.BoneName);
		}

		return true;
	}

	return false;
}
