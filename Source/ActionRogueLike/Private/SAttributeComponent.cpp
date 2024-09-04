// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ... 
	HealthMax = 120;
	Health = HealthMax;
}

bool USAttributeComponent::IsAlive() const
{
	return Health>0.0f;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

float USAttributeComponent::GetHealth() const
{
	return Health;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	 USAttributeComponent* AttributeComp = GetAttributes((Actor));
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor,float Delta)
{

	float OldHealth = Health;

	Health = FMath::Clamp(Health+Delta,0.0f,HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor,this,Health,ActualDelta);
	return ActualDelta != 0;
}
 


