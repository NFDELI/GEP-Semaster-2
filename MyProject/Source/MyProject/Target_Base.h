// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target_Base.generated.h"

UCLASS(Abstract)
class MYPROJECT_API ATarget_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATarget_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ShottedAt();
	virtual void TeleAway();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;
};
