// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNEditorNode_PrimitiveTask.h"
#include "HTaskNetworkAsset.h"
#include "HTaskNetworkEditorPins.h"

UHTNEditorNode_PrimitiveTask::UHTNEditorNode_PrimitiveTask()
{
	Task = CreateDefaultSubobject<UHTaskNetworkTask_Primitive>(TEXT("Task"));
}

void UHTNEditorNode_PrimitiveTask::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, UHTaskNetworkEditorPins::PinCategory_SingleComposite, TEXT("In"));
}

FText UHTNEditorNode_PrimitiveTask::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(Task->Name);
}

FText UHTNEditorNode_PrimitiveTask::GetTooltipText() const
{
	return FText();
}

void UHTNEditorNode_PrimitiveTask::AutowireNewNode(UEdGraphPin* FromPin)
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
