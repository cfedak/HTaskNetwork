#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "Effect.generated.h"

UCLASS()
class HTASKNETWORKRUNTIME_API UEffect : public UObject
{
	GENERATED_BODY()
public:
	virtual void Apply(FWorldState& WorldState) {};
};

UCLASS()
class HTASKNETWORKRUNTIME_API USetEffect : public UEffect
{
	GENERATED_BODY()
	UPROPERTY()
		FName Key;
	UPROPERTY()
		FString Value;
public:
	void Init(FName InKey, FString InValue)
	{
		Key = InKey;
		Value = InValue;
	}

	virtual void Apply(FWorldState& WorldState) override
	{
		if (WorldState.Contains(Key))
		{
			WorldState[Key] = Value;
		}
		else 
		{
			WorldState.Emplace(Key, Value);
		}
	}
};
