#include "HTNEditorNode_Root.h"

#include "HTaskNetworkEditorPins.h"

UHTNEditorNode_Root::UHTNEditorNode_Root()
{
	bIsReadOnly = true;
}

void UHTNEditorNode_Root::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	CreatePin(EEdGraphPinDirection::EGPD_Output, UHTaskNetworkEditorPins::PinCategory_SingleTask, TEXT("Out"));
}

FText UHTNEditorNode_Root::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("FHTaskNetworkEditorModule", "Root", "ROOT");
}

FText UHTNEditorNode_Root::GetTooltipText() const
{
	return Super::GetTooltipText();
}
