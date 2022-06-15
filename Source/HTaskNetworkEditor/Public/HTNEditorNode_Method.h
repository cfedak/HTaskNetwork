// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGraphNode.h"
#include "HTaskNetworkAsset.h"
#include "HTNEditorNode_Method.generated.h"


/**
 * 
 */
UCLASS()
class HTASKNETWORKEDITOR_API UHTNEditorNode_Method : public UAIGraphNode
{
	GENERATED_BODY()
public: 
	UHTNEditorNode_Method();
	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	//~ End UEdGraphNode Interface

	UPROPERTY()
		TObjectPtr<UHTaskNetworkMethod> Method;

};
