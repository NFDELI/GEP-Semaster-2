#include "Collectable.h"

#include "Components/SphereComponent.h"

// Sets default values
ACollectable::ACollectable()
{
	_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = _Collision;
}

void ACollectable::BroadcastCollected(AController* causer)
{
	OnCollected.Broadcast(this, causer);
	Destroy();
}


