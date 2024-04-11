// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* MyPawn =  UGameplayStatics::GetPlayerPawn(this,0);
	if(MyPawn != nullptr)
	{
		//使AI移动至角色初始位置
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation",MyPawn->GetActorLocation());

		//使AI移动至角色当前位置
		GetBlackboardComponent()->SetValueAsObject("TargetActor",MyPawn);

		
	}
}
