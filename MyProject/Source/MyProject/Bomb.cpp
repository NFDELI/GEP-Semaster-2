#include "Bomb.h"

#include "GEPPlayerController.h"
#include "Components/SphereComponent.h"

// Sets default values
ABomb::ABomb()
{
	_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = _Collision;
	_Damage = 50.0f;
}

void ABomb::BombCollided(AController* causer)
{
	if(AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(causer))
	{
		castedPC->DecreaseHp(_Damage);
	}
	Destroy();
}


