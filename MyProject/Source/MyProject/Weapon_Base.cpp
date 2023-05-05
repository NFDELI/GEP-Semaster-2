#include "Weapon_Base.h"

#include "HairStrandsInterface.h"
#include "MovieSceneSequenceID.h"
#include "Blueprint/UserWidget.h"
#include "EntitySystem/MovieSceneComponentTypeInfo.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBase, Display, All);

AWeapon_Base::AWeapon_Base()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);

	//_HealthUI = CreateAbstractDefaultSubobject<UPlayerStatsUIWidget>(TEXT("UI"));
	
	//_MaxBullets = 5.0;
	_CurrentBullets = _MaxBullets;
}

bool AWeapon_Base::Fire_Implementation()
{
	UE_LOG(LogWeaponBase, Display, TEXT("Firing the base weapon class!"));
	return true;
}

bool AWeapon_Base::Reload_Implementation()
{
	UE_LOG(LogWeaponBase, Display, TEXT("Reload! the base weapon class!"));
	return true;
}

bool AWeapon_Base::Bullet_Spent()
{
	//Gun still have bullets.
	if(_CurrentBullets > 0)
	{
		_CurrentBullets--;
		UGameplayStatics::SpawnEmitterAttached(_MuzzleFlash, _Mesh,TEXT("Muzzle"), FVector(0, 0, 0), FRotator(0, 0, 0), FVector(0.2));
		//_HealthUI->UpdateHealthBar(0.1f);
		//CALL UPDATE HEALTH HERE.
		//_PlayerWidget->UpdateHealthBar(.1f);
		
		return true;
	}

	//Gun ran out of bullets, return false;
	return false;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
}

