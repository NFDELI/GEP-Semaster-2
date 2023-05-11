#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

class USphereComponent;
UCLASS(Abstract)
class MYPROJECT_API ABomb : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABomb();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collision;

	UFUNCTION(BlueprintCallable)
	void BombCollided(AController* causer);
	
	float _Damage;

public:

};
