#include "Weapon_Projectile.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

bool AWeapon_Projectile::Fire_Implementation()
{
	UE_LOG(LogWeaponProj, Display, TEXT("Firing projectile weapon class!"));
	if(Bullet_Spent())
	{
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
	return false;
}

bool AWeapon_Projectile::Reload_Implementation()
{
	//Only reload when possible.
	if(_CurrentBullets <= _MaxBullets)
	{
		UE_LOG(LogWeaponProj, Display, TEXT("Reloading! projectile weapon class"));
		//Reload the gun (call in blueprint)
		_CurrentBullets = _MaxBullets;
		return true;
	}
	return false;
}
