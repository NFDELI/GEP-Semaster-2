// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleCompletedSignature, class UGameRule*, rule);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointsScoredSignature, AController*, scorer, int, points);

UCLASS(Abstract, ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameRule();

	FGameRuleCompletedSignature OnGameRuleCompleted;
	FGameRulePointsScoredSignature OnGameRulePointsScored;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsOptional;

	UFUNCTION()
	virtual void Init();

protected:
	void BroadcastGameRuleCompleted();
	void BroadcastGameRulePointsScored(AController* scorer, int points);
};
