#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "PrimitiveTask.generated.h"

USTRUCT()
struct HTASKNETWORKRUNTIME_API FPrimitiveTask
{
	GENERATED_BODY()

	UPROPERTY()
		TArray<class UCondition*> Conditions;

	UPROPERTY()
		class UOperator* Operator;

	bool ConditionsMet(const FWorldState& WorldState);
};