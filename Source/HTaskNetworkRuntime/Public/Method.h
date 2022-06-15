#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "Method.generated.h"

USTRUCT()
struct HTASKNETWORKRUNTIME_API FMethod
{
	GENERATED_BODY();

	UPROPERTY()
		TArray<class UCondition*> Conditions;
	UPROPERTY()
		TArray<FName> Subtasks;

	bool ConditionsMet(const FWorldState& State) const;
};