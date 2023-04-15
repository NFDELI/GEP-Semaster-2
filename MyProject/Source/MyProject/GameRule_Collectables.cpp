#include "GameRule_Collectables.h"

#include "Collectable.h"
#include "Kismet/GameplayStatics.h"

UGameRule_Collectables::UGameRule_Collectables()
{
	_AmountRemaining = 0;
}

void UGameRule_Collectables::Init()
{
	if(_Collectables.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectable::StaticClass(), outActors);
		for(AActor* a : outActors)
		{
			_Collectables.Add(Cast<ACollectable>(a));
		}

		_AmountRemaining = _Collectables.Num();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black,
			FString::Printf(TEXT("GameRule_Collectables: Found %d Collectables in world"), _AmountRemaining));
		for(ACollectable* col : _Collectables)
		{
			col->OnCollected.AddDynamic(this, &UGameRule_Collectables::Handle_Collected);
		}
	}
	
	Super::Init();
}

void UGameRule_Collectables::Handle_Collected(ACollectable* subject, AController* causer)
{
	_AmountRemaining--;
	BroadcastGameRulePointsScored(causer, 1);

	if(_AmountRemaining == 0)
	{
		BroadcastGameRuleCompleted();
	}
}
