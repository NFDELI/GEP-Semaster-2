#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponHitscan, Display, All);

bool AWeapon_Hitscan::Fire_Implementation()
{
	UE_LOG(LogWeaponHitscan, Display, TEXT("Firing hitscan weapon class!"));

	UWorld* const world = GetWorld();
	if(world == nullptr) { return false; }

	FHitResult hit(ForceInit);
	FVector start = _Muzzle->GetComponentLocation();
	FVector end = start + (_Muzzle->GetForwardVector() * 1000);
	TArray<AActor*> ActorsToIgnore;

	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
		FLinearColor::Green, 5))
	{
		UE_LOG(LogWeaponHitscan, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString())
	}

	return true;
}
