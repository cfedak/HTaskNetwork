#pragma once
#include "AIGraphNode.h"
#include "HTNEditorNode_Root.generated.h"

UCLASS()
class HTASKNETWORKEDITOR_API UHTNEditorNode_Root : public UAIGraphNode
{
	GENERATED_BODY()
public: 
	UHTNEditorNode_Root();
	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	//~ End UEdGraphNode Interface
};
