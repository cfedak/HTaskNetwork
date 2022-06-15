#pragma once

#include "CoreMinimal.h"
#include "PrimitiveTask.h"
#include "CompoundTask.h"
#include "HTNDomain.generated.h"

USTRUCT()
struct HTASKNETWORKRUNTIME_API FHTNDomain
{
	GENERATED_BODY()

	UPROPERTY()
		TMap<FName, FPrimitiveTask> PrimitiveTasks;
	UPROPERTY()
		TMap<FName, FCompoundTask> CompoundTasks;

	UPROPERTY()
		FName RootTask;

	bool IsCompoundTask(FName TaskName) const;
	FCompoundTask& CompoundTask(FName Task)
	{
		if (RootTask == NAME_None)
		{
			RootTask = Task;
		}
		if (!CompoundTasks.Contains(Task))
		{
			return CompoundTasks.Emplace(Task);
		}
		return  CompoundTasks[Task];
	}

	FPrimitiveTask& PrimitiveTask(FName Task)
	{
		if (!PrimitiveTasks.Contains(Task))
		{
			return PrimitiveTasks.Emplace(Task);
		}
		return PrimitiveTasks[Task];
	}
};
