#include "SDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h" 


ASDashProjectile::ASDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;
	
	MovementComp->InitialSpeed = 6000.0f;
}
 
void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
 
	// 到爆炸时间后，触发Explode()
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASDashProjectile::Explode, DetonateDelay);
}
 
void ASDashProjectile::Explode_Implementation()
{
	// 可能有碰到障碍物提前爆炸的情况，因此要清除Timer防止被调用两次
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	// 爆炸特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
 
	// 粒子爆炸后关闭系统、停止移动、停止碰撞
	EffectComp->DeactivateSystem();
	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
 
	// 到传送时间后，触发传送
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);
 
	// 不调用base中的Explode中的destroy自身，因为传送时间计时器需要一点时间
	//Super::Explode_Implementation();
}
 
void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		// 传送时保持角色原始Rotation
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
	// 之前没有调用，现在销毁
	Destroy();
}