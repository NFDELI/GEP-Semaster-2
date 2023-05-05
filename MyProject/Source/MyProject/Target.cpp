#include "Target.h"

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

UTarget::UTarget()
{
}

void UTarget::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_HealthComp = owner->FindComponentByClass<UHealthComponent>();
	if(_HealthComp == nullptr)
	{
		_HealthComp = NewObject<UHealthComponent>(owner, TEXT("Health"));
		owner->AddInstanceComponent(_HealthComp);
		_HealthComp->RegisterComponent();
		owner->Modify();
	}

	owner->Tags.Add(FName("GameRuleTarget"));

	_HealthComp->onComponentDead.AddDynamic(this, &UTarget::Handle_Dead);
}

void UTarget::Handle_Dead(AController* causer)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _ParticleDeath, GetOwner()->GetActorLocation());
	OnTargetDestroyed.Broadcast(GetOwner(), causer);
	GetOwner()->Destroy();
}
