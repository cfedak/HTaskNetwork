#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "Effect.h"
#include "Operator.generated.h"

UCLASS()
class HTASKNETWORKRUNTIME_API UOperator : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<class UEffect*> Effects;

	virtual void Apply(FWorldState& WorldState);
};
