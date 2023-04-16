#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	_MaxHealth = 100.f;
	_MaxShield = 100.f;
	_CanRegenShield = true;
	_ShieldRecoverRate = 10.f;
	_ShieldRecoverDelay = 2.f;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	_CurrentHealth = _MaxHealth;
	_CurrentShield = _MaxShield;
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigator, AActor* causer)
{
	float leftOverDamage = FMath::Max(damage - _CurrentShield, 0.f);
	_CurrentShield = FMath::Max(_CurrentShield - damage, 0.f);
	_ShieldRecoverDelayTimer = _ShieldRecoverDelay;

	if(leftOverDamage > 0.f) {_CurrentHealth = FMath::Max(_CurrentHealth - leftOverDamage, 0.f); }

	if(_CurrentHealth <= 0.f) {onComponentDead.Broadcast(instigator);}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(_CurrentShield == _MaxShield || !_CanRegenShield) { return; }

	if(_ShieldRecoverDelayTimer > 0.f)
	{
		_ShieldRecoverDelayTimer -= DeltaTime;
	}
	else
	{
		_CurrentShield = FMath::Min(_MaxShield, _CurrentShield + (_ShieldRecoverRate * DeltaTime));
	}
}

