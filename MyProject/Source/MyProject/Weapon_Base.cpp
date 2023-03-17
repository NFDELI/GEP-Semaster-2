#include "Weapon_Base.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBase, Display, All);

AWeapon_Base::AWeapon_Base()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	_Mesh->SetupAttachment(_Root);

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
}

bool AWeapon_Base::Fire_Implementation()
{
	UE_LOG(LogWeaponBase, Display, TEXT("Firing the base weapon class!"));
	return true;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
}
