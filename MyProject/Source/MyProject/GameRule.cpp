#include "GameRule.h"

UGameRule::UGameRule()
{
	_IsOptional = false;
}

void UGameRule::Init()
{
}

void UGameRule::BroadcastGameRuleCompleted()
{
	OnGameRuleCompleted.Broadcast(this);
}

void UGameRule::BroadcastGameRulePointsScored(AController* scorer, int points)
{
	OnGameRulePointsScored.Broadcast(scorer, points);
}
