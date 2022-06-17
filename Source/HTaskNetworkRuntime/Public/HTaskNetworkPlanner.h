// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "HTNDecompHistoryItem.h"
#include "HTaskNetworkDomain.h"
#include "HTaskNetworkPlanner.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKRUNTIME_API UHTaskNetworkPlanner: public UObject
{
	GENERATED_BODY()
protected:
	TArray<FHTNDecompHistoryItem> DecompHistoryStack;
	FWorldState WorkingWorldState;
	TArray<FName> TasksToProcess;
	TArray<FName> FinalPlan;
	FName CurrentTask;
public:
	UHTaskNetworkPlanner();
	~UHTaskNetworkPlanner();

	bool CreatePlan(FHTaskNetworkDomain& Domain, FWorldState WorldState, TArray<FName>& PlanOut);
	void RecordDecompositionOfTask();
	void RestoreToLastDecomposedTask();
};
