#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Collectables.generated.h"

class ACollectable;
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UGameRule_Collectables : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_Collectables();

	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACollectable>> _Collectables;

	int _AmountRemaining;

	UFUNCTION()
	void Handle_Collected(ACollectable* subject, AController* causer);
};
