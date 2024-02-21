
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
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
