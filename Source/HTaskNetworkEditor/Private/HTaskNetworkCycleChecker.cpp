// Fill out your copyright notice in the Description page of Project Settings.


#include "HTaskNetworkCycleChecker.h"

bool FHTaskNetworkCycleChecker::CheckForLoop(const UEdGraphNode* StartNode, const UEdGraphNode* EndNode)
{
	VisitedNodes.Add(StartNode);
	return TraverseNodes(EndNode);
}

bool FHTaskNetworkCycleChecker::TraverseNodes(const UEdGraphNode* Node)
{
	VisitedNodes.Add(Node);

	for (auto MyPin : Node->Pins)
	{
		if (MyPin->Direction == EGPD_Output)
		{
			for (auto OtherPin : MyPin->LinkedTo)
			{
				UEdGraphNode* OtherNode = OtherPin->GetOwningNode();
				if (VisitedNodes.Contains(OtherNode))
				{
					// Only  an issue if this is a back-edge
					return false;
				}
				else if (!FinishedNodes.Contains(OtherNode))
				{
					// Only should traverse if this node hasn't been traversed
					if (!TraverseNodes(OtherNode))
						return false;
				}
			}
		}
	}

	VisitedNodes.Remove(Node);
	FinishedNodes.Add(Node);
	return true;
}
