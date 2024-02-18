// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UParticleSystemComponent* EffectComp;


	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;//VFX指Visual effects, 即视觉特效，负责爆炸时的特效
 
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode(); // 爆炸函数



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
