// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree,TEXT("Behavior Tree is a nullptr! Please assign BehaviorTree in Your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);

	}


	/*APawn* MyPawn =  UGameplayStatics::GetPlayerPawn(this,0);
	if(MyPawn != nullptr)
	{
		//使AI移动至角色初始位置
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation",MyPawn->GetActorLocation());

		//使AI移动至角色当前位置
		GetBlackboardComponent()->SetValueAsObject("TargetActor",MyPawn);

		
	}*/
	//上面注释的代码已经不需要了

	
}
