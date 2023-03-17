// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectProjectile.h"
#include "Weapon_Base.h"
#include "GameFramework/Actor.h"
#include "Weapon_Projectile.generated.h"

UCLASS(Abstract)
class MYPROJECT_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyProjectProjectile> _Projectile;

public:
	virtual bool Fire_Implementation() override;
};
