#include "GraphPanelNodeFactory_HTaskNetwork.h"
#include "AIGraphNode.h"
#include "SGraphNode_TaskNetwork.h"

FGraphPanelNodeFactory_HTaskNetwork::FGraphPanelNodeFactory_HTaskNetwork()
{

}

FGraphPanelNodeFactory_HTaskNetwork::~FGraphPanelNodeFactory_HTaskNetwork()
{

}

TSharedPtr<class SGraphNode> FGraphPanelNodeFactory_HTaskNetwork::CreateNode(UEdGraphNode* Node) const
{
	if (auto AIGraphNode = Cast<UAIGraphNode>(Node))
	{
		return SNew(SGraphNode_TaskNetwork, AIGraphNode);
	}
	return nullptr;
}
