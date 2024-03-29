// Fill out your copyright notice in the Description page of Project Settings.


#include "HTaskNetworkPlanner.h"
#include "Operator.h"

UHTaskNetworkPlanner::UHTaskNetworkPlanner()
{
}

UHTaskNetworkPlanner::~UHTaskNetworkPlanner()
{
}

bool UHTaskNetworkPlanner::CreatePlan(FHTaskNetworkDomain& Domain, FWorldState WorldState, TArray<FName>& PlanOut)
{
	WorkingWorldState = WorldState;
	DecompHistoryStack.Reset();
	FinalPlan.Reset();
	TasksToProcess.Reset();
	TasksToProcess.Add(Domain.RootTask);

	while (TasksToProcess.Num() > 0)
	{
		CurrentTask = TasksToProcess.Pop();
		if (Domain.IsCompoundTask(CurrentTask))
		{
			FCompoundTask CompoundTask = Domain.CompoundTasks[CurrentTask];
			FMethod Method;
			if (CompoundTask.FindSatisfiedMethod(WorkingWorldState, Method))
			{
				RecordDecompositionOfTask();
				TasksToProcess.Insert(Method.Subtasks, 0);
			}
			else
			{
				RestoreToLastDecomposedTask();
			}
		} 
		else
		{
			FPrimitiveTask PrimitiveTask = Domain.PrimitiveTasks[CurrentTask];
			if (PrimitiveTask.ConditionsMet(WorkingWorldState))
			{
				PrimitiveTask.Operator->Apply(WorldState);
				FinalPlan.Push(CurrentTask);
			}
		}
	}
	if (FinalPlan.Num()== 0)
	{
		PlanOut.Reset();
		return false;
	}
	PlanOut = FinalPlan;
	return true;
}

void UHTaskNetworkPlanner::RecordDecompositionOfTask()
{
	DecompHistoryStack.Emplace();
	DecompHistoryStack.Last().CurrentTask = CurrentTask;
	DecompHistoryStack.Last().State = WorkingWorldState;
	DecompHistoryStack.Last().TasksToProcess = TasksToProcess;
	DecompHistoryStack.Last().FinalPlan = FinalPlan;
}

void UHTaskNetworkPlanner::RestoreToLastDecomposedTask()
{
	FHTNDecompHistoryItem Item = DecompHistoryStack.Pop();
	WorkingWorldState = Item.State;
	TasksToProcess = Item.TasksToProcess;
	FinalPlan = Item.FinalPlan;
	CurrentTask = Item.CurrentTask;
}
