#include "SGraphNodeAI.h"

#pragma once

class SGraphNode_TaskNetwork: public SGraphNodeAI
{
public:
    SLATE_BEGIN_ARGS(SGraphNode_TaskNetwork) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, UAIGraphNode* InNode);

    // SGraphNode interface
	virtual void UpdateGraphNode() override;
    virtual void CreatePinWidgets() override;
};