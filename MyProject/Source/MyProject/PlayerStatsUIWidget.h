// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ProgressBar.h"
#include "PlayerStatsUIWidget.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS(Abstract)
class MYPROJECT_API UPlayerStatsUIWidget : public UBaseWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	//UProgressBar* HealthBar;

public:
	virtual void NativeConstruct() override;
	void UpdateHealthBar(float value);
};
