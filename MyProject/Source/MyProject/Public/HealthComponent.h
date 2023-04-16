// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*, causer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Components")
	FComponentDeadSignature onComponentDead;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float _CurrentHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float _MaxHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shield")
	float _CurrentShield;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shield")
	float _MaxShield;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shield")
	bool _CanRegenShield;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shield")
	float _ShieldRecoverDelayTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shield")
	float _ShieldRecoverRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float _ShieldRecoverDelay;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);
	

		
};
