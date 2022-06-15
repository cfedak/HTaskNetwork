// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNEditorNode_CompoundTask.h"
#include "HTaskNetworkEditorPins.h"

UHTNEditorNode_CompoundTask::UHTNEditorNode_CompoundTask()
{
	Task = CreateDefaultSubobject<UHTaskNetworkTask_Compound>(TEXT("Task"));
}

void UHTNEditorNode_CompoundTask::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, UHTaskNetworkEditorPins::PinCategory_SingleComposite, TEXT("In"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, UHTaskNetworkEditorPins::PinCategory_MultipleMethods, TEXT("Out"));
}

FText UHTNEditorNode_CompoundTask::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(Task->Name);
}

FText UHTNEditorNode_CompoundTask::GetTooltipText() const
{
	return FText();
}

void UHTNEditorNode_CompoundTask::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}
