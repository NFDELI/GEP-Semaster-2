#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponHitScan, Display, All);

bool AWeapon_Hitscan::Fire_Implementation()
{
	UE_LOG(LogWeaponHitScan, Display, TEXT("Firing hitscan weapon class"));

	UWorld* const world = GetWorld();
	if(world == nullptr)
	{
		return false;
	}

	FHitResult hit(ForceInit);
	FVector start = _Muzzle->GetComponentLocation();
	FVector end = start + (_Muzzle->GetForwardVector() * 1000);
	TArray<AActor*> ActorsToIgnore;

	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
		FLinearColor::Green, 5))
	{
		//Do damage here?
		UE_LOG(LogWeaponHitScan, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString());
	}

	return true;
}
