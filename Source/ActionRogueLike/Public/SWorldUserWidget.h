// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;


public:
	UPROPERTY(BlueprintReadWrite,Category="UI",meta = (ExposeOnSpawn = true))
	AActor* AttachedActor;

	UPROPERTY(BlueprintReadOnly,Category="UI")
	FVector WorldOffset;
};
