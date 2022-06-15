#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
#include "Condition.generated.h"

UCLASS()
class HTASKNETWORKRUNTIME_API UCondition : public UObject
{
	GENERATED_BODY()
public:
	virtual bool Test(const FWorldState& WorldState) { return true; };
};

UCLASS()
class HTASKNETWORKRUNTIME_API UEqualCondition : public UCondition
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		FName Key;
	UPROPERTY()
		FString Value;
public:
	void Init(FName InKey, FString ShouldBe) {
		Key = InKey;
		Value = ShouldBe;
	}
	virtual bool Test(const FWorldState& WorldState) 
	{ 
		if (!WorldState.Contains(Key))
		{
			return false;
		}
		return WorldState[Key].Equals(Value);
	};
};
