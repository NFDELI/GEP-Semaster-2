// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsUIWidget.h"

#include "Components/ProgressBar.h"


void UPlayerStatsUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(HealthBar)
	{
		HealthBar->SetPercent(1);
	}
}

void UPlayerStatsUIWidget::UpdateHealthBar(float value)
{
	HealthBar->SetPercent(value);
}
