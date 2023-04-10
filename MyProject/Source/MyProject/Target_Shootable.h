// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target_Base.h"
#include "GameFramework/Actor.h"
#include "Target_Shootable.generated.h"

UCLASS(Abstract)
class MYPROJECT_API ATarget_Shootable : public ATarget_Base
{
	GENERATED_BODY()

public:
	ATarget_Shootable();
	
	virtual void ShottedAt(float damage) override;
	void ColorChange();
	void TakeDamage(float damage);
	void TargetDeath();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _CurrentHealth;
};
