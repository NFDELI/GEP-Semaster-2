#include "Widget_Score.h"

#include "Components/TextBlock.h"

void UWidget_Score::NativeConstruct()
{
	Super::NativeConstruct();

	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score: 0"));
	}
}

void UWidget_Score::UpdateScore(int score)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), score)));
	}
}
