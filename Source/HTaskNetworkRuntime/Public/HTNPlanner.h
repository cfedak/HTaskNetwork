// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "HTNDecompHistoryItem.h"
#include "HTNDomain.h"
#include "HTNPlanner.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKRUNTIME_API UHTNPlanner: public UObject
{
	GENERATED_BODY()
protected:
	TArray<FHTNDecompHistoryItem> DecompHistoryStack;
	FWorldState WorkingWorldState;
	TArray<FName> TasksToProcess;
	TArray<FName> FinalPlan;
	FName CurrentTask;
public:
	UHTNPlanner();
	~UHTNPlanner();

	bool CreatePlan(FHTNDomain& Domain, FWorldState WorldState, TArray<FName>& PlanOut);
	void RecordDecompositionOfTask();
	void RestoreToLastDecomposedTask();
};
