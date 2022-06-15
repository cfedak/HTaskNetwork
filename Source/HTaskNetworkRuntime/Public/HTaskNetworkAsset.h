// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTaskNetworkAsset.generated.h"

class UHTaskNetworkCompoundTask;
class UHTaskNetworkMethod;
class UHTaskNetworkPrimitiveTask;

/**
 * 
 */
UCLASS(BlueprintType)
class HTASKNETWORKRUNTIME_API UHTaskNetworkAsset : public UObject
{
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
	/** Graph for Behavior Tree */
	UPROPERTY()
	TObjectPtr<class UEdGraph> HTNGraph;
#endif

	UPROPERTY()
		TObjectPtr<UHTaskNetworkTask_Compound> RootNode;
};

USTRUCT()
struct FTaskNetworkMethodChild {
	GENERATED_BODY()
public:
	UPROPERTY()
		TObjectPtr<UHTaskNetworkTask_Compound> CompoundChild = nullptr;
	UPROPERTY()
		TObjectPtr<UHTaskNetworkTask_Primitive> PrimitiveChild = nullptr;
};

UCLASS()
class HTASKNETWORKRUNTIME_API UHTaskNetworkMethod: public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Name = TEXT("Method");
	UPROPERTY()
		TArray<FTaskNetworkMethodChild> SubTasks;
};

UCLASS()
class HTASKNETWORKRUNTIME_API UHTaskNetworkTask_Compound : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Name = TEXT("Compound");

	UPROPERTY()
	TArray<TObjectPtr<UHTaskNetworkMethod>> Methods;
};

UCLASS()
class HTASKNETWORKRUNTIME_API UHTaskNetworkTask_Primitive : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Name = TEXT("Primitive");
};



