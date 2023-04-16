#include "Target.h"

UTarget::UTarget()
{
}

void UTarget::BeginPlay()
{
	//Super::BeginPlay();

	//AActor* owner = GetOwner();
	//_HealthComp = owner->FindComponentByClass<UHealthComponent>();
	//if(_HealthComp == nullptr)
	//{
	//	_HealthComp = NewObject<UHealthComponent>(owner, TEXT("Health"));
	//	owner->AddInstanceComponent(_HealthComp);
	//	_HealthComp->RegisterComponent();
	//	owner->Modify();
	//}
}

void UTarget::Handle_Dead(AController* causer)
{
	OnTargetDestroyed.Broadcast(GetOwner(), causer);
	GetOwner()->Destroy();
}
