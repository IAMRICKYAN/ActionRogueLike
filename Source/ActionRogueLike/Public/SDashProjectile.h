// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()


	
public:
 
	ASDashProjectile();
 
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay; // 传送延迟
 
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay; // 爆炸延迟
	

 
	// hit后清除计时器
	FTimerHandle TimerHandle_DelayedDetonate;
 
	virtual void Explode_Implementation() override;
 
	void TeleportInstigator();
 
	virtual void BeginPlay() override;

};
