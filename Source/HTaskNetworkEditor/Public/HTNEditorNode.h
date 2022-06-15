// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGraphNode.h"
#include "HTNEditorNode.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKEDITOR_API UHTNEditorNode : public UAIGraphNode
{
	GENERATED_BODY()
public:
	virtual FText GetDescription() const override;
};
