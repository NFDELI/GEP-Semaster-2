// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "GEPChar.h"
#include "PlayerStatsUIWidget.h"
#include "Widget_Score.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGEPPlayerController::AGEPPlayerController() : Super()
{
	_Score = 0;
	_Hp = 1.0f;
}

void AGEPPlayerController::Init_Implementation()
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		//Turning On Controllers.
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if(GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}

	if(_ScoreWidgetClass)
	{
		_ScoreWidget = CreateWidget<UWidget_Score, AGEPPlayerController*>(this, _ScoreWidgetClass.Get());
		_ScoreWidget->AddToViewport();
	}

	if(_HpProgressBarClass)
	{
		_HpProgressBar = CreateWidget<UPlayerStatsUIWidget, AGEPPlayerController*>(this, _HpProgressBarClass.Get());
		_HpProgressBar->AddToViewport();
	}
}

void AGEPPlayerController::Handle_MatchStarted_Implementation()
{
	UWorld* const world = GetWorld();

	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLocation = tempStart != nullptr ? tempStart->GetActorLocation() : FVector::ZeroVector;
	FRotator spawnRotation = tempStart != nullptr ? tempStart->GetActorRotation() : FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = world->SpawnActor<APawn>(_PawnToSpawn, spawnLocation, spawnRotation, spawnParams);
	Possess(tempPawn);

	if(AGEPChar* castedPawn = Cast<AGEPChar>(tempPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init();
	}
}

void AGEPPlayerController::Handle_MatchEnded_Implementation()
{
	//SetInputMode(FInputModeUIOnly());
}

void AGEPPlayerController::AddScore(int amount)
{
	_Score += amount;
	if(_ScoreWidget != nullptr)
	{
		_ScoreWidget->UpdateScore(_Score);
	}
}

void AGEPPlayerController::DecreaseHp(float amount)
{
	_Hp -= amount / 100;
	if(_HpProgressBar != nullptr)
	{
		_HpProgressBar->UpdateHealthBar(_Hp);
	}
}
