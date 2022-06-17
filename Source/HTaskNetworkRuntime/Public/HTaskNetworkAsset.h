// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTaskNetworkAsset.generated.h"

class UHTaskNetworkTask_Primitive;
class UHTaskNetworkTask_Compound;

USTRUCT(BlueprintType)
struct FTaskNetworkMethodChild {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHTaskNetworkTask_Compound> CompoundChild = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHTaskNetworkTask_Primitive> PrimitiveChild = nullptr;
};

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

	UPROPERTY(BlueprintReadOnly)
		FTaskNetworkMethodChild RootNode;
};

UCLASS(BlueprintType)
class HTASKNETWORKRUNTIME_API UHTaskNetworkMethod: public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name = TEXT("Method");
	UPROPERTY(BlueprintReadOnly)
		TArray<FTaskNetworkMethodChild> SubTasks;
};

UCLASS(BlueprintType)
class HTASKNETWORKRUNTIME_API UHTaskNetworkTask_Compound : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name = TEXT("Compound");

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UHTaskNetworkMethod>> Methods;
};

UCLASS(BlueprintType)
class HTASKNETWORKRUNTIME_API UHTaskNetworkTask_Primitive : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name = TEXT("Primitive");
};



