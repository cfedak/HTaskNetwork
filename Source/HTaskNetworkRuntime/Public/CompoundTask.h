#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "Method.h"
#include "CompoundTask.generated.h"

USTRUCT()
struct HTASKNETWORKRUNTIME_API FCompoundTask
{
	GENERATED_BODY()

	UPROPERTY()
		TArray<FMethod> Methods;

	bool FindSatisfiedMethod(FWorldState& State, FMethod& OutMethod);
};
