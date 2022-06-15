#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "HTNDecompHistoryItem.generated.h"

USTRUCT()
struct HTASKNETWORKRUNTIME_API FHTNDecompHistoryItem
{
	GENERATED_BODY()

	FWorldState State;
	TArray<FName> TasksToProcess;
	TArray<FName> FinalPlan;
	FName CurrentTask;
};