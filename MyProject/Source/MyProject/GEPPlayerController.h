// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "GEPPlayerController.generated.h"

class UInputMappingContext;
class UWidget_Score;
class UWidget_Bullets;
class UPlayerStatsUIWidget;

UCLASS(Abstract)
class MYPROJECT_API AGEPPlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()
	
public:
	AGEPPlayerController();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

	void AddScore(int amount);
	void DecreaseHp(float amount);
	void ChangeAmmo(int ammo, int maxAmmo);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _PawnToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Score> _ScoreWidgetClass;
	TObjectPtr<UWidget_Score> _ScoreWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Bullets> _AmmoCounterClass;
	TObjectPtr<UWidget_Bullets> _AmmoCounter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerStatsUIWidget> _HpProgressBarClass;
	TObjectPtr<UPlayerStatsUIWidget> _HpProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	int _Score;
	float _Hp;
	int _Ammo;
};
