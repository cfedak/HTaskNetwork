// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrainComponent.h"
#include "HTaskNetworkAsset.h"
#include "HTaskNetworkBrainComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HTASKNETWORKRUNTIME_API UHTaskNetworkBrainComponent : public UBrainComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	// Not really doing anything with this yet, but this lets us set
	// the object in the editor
	UHTaskNetworkAsset* TaskNetwork;
	
};
