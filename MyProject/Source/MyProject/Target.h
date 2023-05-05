//This code is for GEP Videos Week 6 part2....
#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "Target.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDestroyedSignature, AActor*, target, AController*, delegateInstigator);

//class UHealthComponent;
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UTarget : public UActorComponent
{
	GENERATED_BODY()

public:
	UTarget();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnTargetDestroyed;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _HealthComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> _ParticleDeath;

private:
	UFUNCTION()
	void Handle_Dead(AController* causer);
};
