// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fireable.h"
#include "PlayerStatsUIWidget.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class USkeletalMeshComponent;

UCLASS(Abstract)
class MYPROJECT_API AWeapon_Base : public AActor, public IFireable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Base();

	virtual bool Fire_Implementation() override;
	virtual bool Reload_Implementation() override;
	virtual bool Bullet_Spent();

	//UPROPERTY(EditAnywhere, Category=UI)
	//UPlayerStatsUIWidget* _PlayerWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> _MuzzleFlash;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _CurrentBullets;

	//UFUNCTION(BlueprintCallable, Category="Weapon")
	//void Reload();
};
