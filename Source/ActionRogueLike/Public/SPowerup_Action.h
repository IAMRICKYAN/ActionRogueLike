// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SPowerupActor.h"
#include "SPowerup_Action.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerup_Action : public ASPowerupActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Powerup")
	TSubclassOf<USAction> ActionToGrant;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
