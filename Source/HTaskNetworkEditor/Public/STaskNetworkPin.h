// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNodeAI.h"

/**
 * 
 */
class HTASKNETWORKEDITOR_API STaskNetworkPin: public SGraphPinAI
{
public:
	SLATE_BEGIN_ARGS(STaskNetworkPin){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
protected:
	virtual FSlateColor GetPinColor() const override;
};
