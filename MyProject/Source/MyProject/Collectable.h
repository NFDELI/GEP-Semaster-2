// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollectedSignature, class ACollectable*, subject, AController*, causer);

class USphereComponent;
UCLASS(Abstract)
class MYPROJECT_API ACollectable : public AActor
{
	GENERATED_BODY()

public:
	ACollectable();

	UPROPERTY(BlueprintAssignable)
	FCollectedSignature OnCollected;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collision;

	UFUNCTION(BlueprintCallable)
	void BroadcastCollected(AController* causer);
};
