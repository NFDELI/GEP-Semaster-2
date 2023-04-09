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
	virtual void ShottedAt() override;
	
};
