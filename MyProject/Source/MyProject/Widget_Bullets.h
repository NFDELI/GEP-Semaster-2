#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "Widget_Bullets.generated.h"

class UTextBlock;
UCLASS(Abstract, BlueprintType)
class MYPROJECT_API UWidget_Bullets : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdateAmmo(int ammo, int maxAmmo);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AmmoText;
};
