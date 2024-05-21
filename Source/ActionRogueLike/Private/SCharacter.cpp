// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SAttributeComponent.h"
#include "SDashProjectile.h"
#include "SInteractionComponent.h"
#include "Chaos/ChaosPerfTest.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringarmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");


	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;

	

}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this,&ASCharacter::OnHealthChanged);
	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(),value);
}

void ASCharacter::MoveRight(float value)
{

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector,value);
}



void ASCharacter::PrimaryAttack()
{
	
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimeElasped,0.2f);

	//如果我们的角色死了,使用下面语句清理TimerHandle
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
	

    	
}

void ASCharacter::PrimaryAttack_TimeElasped()
{
		/*FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

    	FTransform SpawnTM = FTransform(GetControlRotation(),HandLocation);
    
    	FActorSpawnParameters SpawnParams;
    	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
    	
    	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);*/

		SpawnProjectile(ProjectileClass);
 	
		
}



void ASCharacter::PrimaryInteract()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
	
}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensure(ClassToSpawn))
	{
		// 获取模型右手位置
		FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");
 	
		// 检测距离为 5000 cm = 50 m
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + ( GetControlRotation().Vector() * 5000 );
 	
		// 检测半径
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
 	
		// 不要检测自己角色
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
 	
		// 碰撞设置
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
 	
		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params)) {
			TraceEnd = Hit.ImpactPoint;
		}
			
		// 尾向量 - 头向量 = 方向向量 eg：起点(0,0) 终点(1,1)，方向向量为(1,1)
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - RightHandLoc).Rotator();
		// 朝向检测到的落点方向，在角色的右手位置生成
		FTransform SpawnTM = FTransform(ProjRotation, RightHandLoc);
 	
		// 此处设置碰撞检测规则为：即使碰撞也总是生成
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		/*
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		*/

		GetWorld()->SpawnActor<AActor>(ClassToSpawn,SpawnTM,SpawnParams);
	}

	
}

void ASCharacter::BlackHoleAttack()
{
	
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack,this,&ASCharacter::BlackHoleAttack_TimeElasped,0.2f);

	//如果我们的角色死了,使用下面语句清理TimerHandle
	//GetWorldTimerManager().ClearTimer(TimerHandle_BlackHoleAttack)
}

void ASCharacter::BlackHoleAttack_TimeElasped()
{
	SpawnProjectile((BlackHoleProjectileClass));
	
}



void ASCharacter::DashAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_DashAttack,this,&ASCharacter::DashAttack_TimeElasped,0.2f);

	//如果我们的角色死了,使用下面语句清理TimerHandle
	//GetWorldTimerManager().ClearTimer(TimerHandle_BlackHoleAttack)
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(NewHealth <= 0.0f && Delta <0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}



void ASCharacter::DashAttack_TimeElasped()
{
	SpawnProjectile((DashProjectileClass));

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("BlackHoleAttack",IE_Pressed,this,&ASCharacter::BlackHoleAttack);

	PlayerInputComponent->BindAction("DashAttack",IE_Pressed,this,&ASCharacter::DashAttack);

}

