#include "CompoundTask.h"

bool FCompoundTask::FindSatisfiedMethod(FWorldState& State, FMethod& OutMethod)
{
	if (Methods.Num() == 0) { return true; }
	for (FMethod& Method : Methods)
	{
		if (Method.ConditionsMet(State))
		{
			OutMethod = Method;
			return true;
		}
	}

	return false;
}
