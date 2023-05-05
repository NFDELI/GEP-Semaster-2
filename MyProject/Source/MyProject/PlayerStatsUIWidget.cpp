#include "PlayerStatsUIWidget.h"

#include "Components/ProgressBar.h"
void UPlayerStatsUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(HealthBar)
	{
		HealthBar->SetPercent(100.0f);
	}
}

void UPlayerStatsUIWidget::UpdateHealthBar(float value)
{
	HealthBar->SetPercent(value);
}
