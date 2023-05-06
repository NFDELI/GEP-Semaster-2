#include "Weapon_Hitscan.h"

#include "PlayerStatsUIWidget.h"
#include "Target_Shootable.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponHitScan, Display, All);

bool AWeapon_Hitscan::Fire_Implementation()
{
	if(Bullet_Spent())
	{
		UE_LOG(LogWeaponHitScan, Display, TEXT("Firing hitscan weapon class"));

		//Attempted to Update Health UI when the player shoots, need help getting reference to the Health UI component.
		//_HealthUI->UpdateHealthBar(0.1f);		
		
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
			ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Blue,
			FLinearColor::Yellow, 5))
		{
			//Do damage here?
			//UE_LOG(LogWeaponHitScan, Display, TEXT("Hit position!!: %s"), *hit.GetActor()->GetActorLabel());
			//UE_LOG(LogWeaponHitScan, Display, TEXT("Hit Class!!: %s"), *hit.GetActor()->GetClass());
			//if(hit.GetActor()->GetActorLabel() == "BP_Target_Shootable")
			//{
			//	UE_LOG(LogWeaponHitScan, Display, TEXT("Hit position!!: %s"), *hit.GetActor()->GetActorLabel());
			//	ATarget_Shootable* temp = Cast<ATarget_Shootable>();
			//	hit.Get
//
			//	//hit.GetActor()->GetClass()
			//}

			UGameplayStatics::ApplyDamage(hit.GetActor(), 100.f, GetInstigatorController(), this, UDamageType::StaticClass());
			if(auto target = Cast<ATarget_Shootable>(hit.GetActor()))
			{
				target->ShottedAt(_GunDamage);
				//UE_LOG(LogWeaponHitScan, Display, TEXT("SHOTAT IS CALLED"));
			}
		}
		return true;
	}

	//Player has no bullets to shoot.
	return false;
}

bool AWeapon_Hitscan::Reload_Implementation()
{
	//Only reload when possible.
	if(_CurrentBullets <= _MaxBullets)
	{
		UE_LOG(LogWeaponHitScan, Display, TEXT("Reloading! hitscan weapon class"));
		//Reload the gun (call in blueprint)
		_CurrentBullets = _MaxBullets;
		_PlayerController->ChangeAmmo(_CurrentBullets, _MaxBullets);
		return true;
	}
	return false;
}

void AWeapon_Hitscan::BeginPlay()
{
	Super::BeginPlay();
}
