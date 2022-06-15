#pragma once
#include "EdGraphUtilities.h"

class FGraphPanelNodeFactory_HTaskNetwork: public FGraphPanelNodeFactory
{
public:
    FGraphPanelNodeFactory_HTaskNetwork();
    virtual ~FGraphPanelNodeFactory_HTaskNetwork();

    virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;

};