#include "Method.h"
#include "Condition.h"

bool FMethod::ConditionsMet(const FWorldState& State) const
{
    if (Conditions.Num() == 0) { return true; }
    for (UCondition* Condition : Conditions)
    {
        if (!Condition->Test(State))
        {
            return false;
        }
    }
    return true;
}
