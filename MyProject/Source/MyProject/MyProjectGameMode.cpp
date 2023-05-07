// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"

#include "GameRule.h"
#include "GEPPlayerController.h"
#include "MyProjectCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
	: Super()
{
	_CountdownTimer = 3;
	_GameRulesLeft = 0;
}

AActor* AMyProjectGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_PlayerStarts.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), _PlayerStarts);
	}
	if(_PlayerStarts.Num() > 0)
	{
		return _PlayerStarts[0];
	}
	return nullptr;
}

void AMyProjectGameMode::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	if(AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(NewPlayer))
	{
		//TODO:: bind to any relevant events.
		castedPC->Init();
	}
	Super::PostLogin(NewPlayer);
}

void AMyProjectGameMode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AMyProjectGameMode::PawnKilled(APawn* PawnKilled)
{
}

void AMyProjectGameMode::DecreaseCountDown()
{
	_CountdownTimer--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), _CountdownTimer));
	if(_CountdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		//If timer is not yet zero, start the countdown again.
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AMyProjectGameMode::DecreaseCountDown, 1.f, false);
	}
}

void AMyProjectGameMode::Handle_GameRuleCompleted(UGameRule* rule)
{
	if(*_GameRuleManagers.Find(rule)) { return; }

	_GameRulesLeft--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black,
		FString::Printf(TEXT("GameRule completed. %d Remaining!"), _GameRulesLeft));

	if(_GameRulesLeft != 0) { return; }

	EndMatch();

	UGameplayStatics::OpenLevel(this, "YouWinMap", true);
}

void AMyProjectGameMode::Handle_GameRulePointsScored(AController* scorer, int points)
{
	if(AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(scorer))
	{
		castedPC->AddScore(points);
	}

	if(AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(scorer))
	{
		castedPC->DecreaseHp(points);
	}
}

void AMyProjectGameMode::Handle_AmmoChange(AController* reloader, int ammo, int maxAmmo)
{
	if(AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(reloader))
	{
		castedPC->ChangeAmmo(ammo, maxAmmo);
	}
}

void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp : outComponents)
	{
		if(UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule, rule->_IsOptional);
			rule->Init();
			rule->OnGameRuleCompleted.AddDynamic(this, &AMyProjectGameMode::Handle_GameRuleCompleted);
			rule->OnGameRulePointsScored.AddDynamic(this, &AMyProjectGameMode::Handle_GameRulePointsScored);
			if(!rule->_IsOptional)
			{
				_GameRulesLeft++;
			}
		}
	}
}

void AMyProjectGameMode::HandleMatchIsWaitingToStart()
{
	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AMyProjectGameMode::DecreaseCountDown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AMyProjectGameMode::HandleMatchHasStarted()
{
	for(AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
	Super::HandleMatchHasStarted();
}

void AMyProjectGameMode::HandleMatchHasEnded()
{
	for(AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(controller);
		}
	}
	Super::HandleMatchHasEnded();
}

void AMyProjectGameMode::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting to Start";
	}
	else if (MatchState == MatchState::InProgress)
	{
		output = "InProgress";
	}
	else if (MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if (MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString::Printf(TEXT("State Changed To: %s"), *output));
	
	Super::OnMatchStateSet();
}

bool AMyProjectGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AMyProjectGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}
