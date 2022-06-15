// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGraphSchema.h"
#include "EdGraphSchema_HTaskNetwork.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKEDITOR_API UEdGraphSchema_HTaskNetwork : public UAIGraphSchema
{
	GENERATED_BODY()
public:
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
};
