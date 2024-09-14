
#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

	

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 球体,用于计算碰撞
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* SphereComp;

	// 投射体，控制球体的运动
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	// 粒子系统，控制特效
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;
	

};
