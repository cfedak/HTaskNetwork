// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HTASKNETWORKEDITOR_API FHTaskNetworkCycleChecker
{
public:
	bool CheckForLoop(const UEdGraphNode* StartNode, const UEdGraphNode* EndNode);
private:
	bool TraverseNodes(const UEdGraphNode* Node);

	TSet<const UEdGraphNode*> VisitedNodes;
	TSet<const UEdGraphNode*> FinishedNodes;
};
