#include "Weapon_Projectile.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

bool AWeapon_Projectile::Fire_Implementation()
{
	UE_LOG(LogWeaponProj, Display, TEXT("Firing projectile weapon class!"));

	UWorld* const world = GetWorld();
	if(world == nullptr || _Projectile == nullptr)
	{
		return false;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	world->SpawnActor(_Projectile, &_Muzzle->GetComponentTransform(), spawnParams);
	
	return true;
}
