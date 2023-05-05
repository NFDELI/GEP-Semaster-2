#include "Widget_Bullets.h"

#include "Components/TextBlock.h"

void UWidget_Bullets::NativeConstruct()
{
	Super::NativeConstruct();

	if(AmmoText)
	{
		AmmoText->SetText(FText::FromString("0/0"));
	}
}

void UWidget_Bullets::UpdateAmmo(int ammo, int maxAmmo)
{
	if(AmmoText)
	{
		AmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), ammo, maxAmmo)));
	}
}
