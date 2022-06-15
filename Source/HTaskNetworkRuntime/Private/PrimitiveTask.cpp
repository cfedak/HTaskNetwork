#include "PrimitiveTask.h"
#include "Condition.h"

bool FPrimitiveTask::ConditionsMet(const FWorldState& WorldState)
{
	if (Conditions.Num() == 0)
	{
		return true;
	}
	for (auto Condition : Conditions)
	{
		if (!Condition->Test(WorldState))
		{
			return false;
		}
	}
	return true;
}
