#include "Operator.h"
#include "Effect.h"

void UOperator::Apply(FWorldState& WorldState)
{
	for (auto Effect : Effects)
	{
		Effect->Apply(WorldState);
	}
}