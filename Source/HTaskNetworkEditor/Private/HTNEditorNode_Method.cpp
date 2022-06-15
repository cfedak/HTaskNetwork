// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNEditorNode_Method.h"
#include "HTaskNetworkAsset.h"
#include "HTaskNetworkEditorPins.h"

UHTNEditorNode_Method::UHTNEditorNode_Method()
{
	Method = CreateDefaultSubobject<UHTaskNetworkMethod>(TEXT("Method"));
}

void UHTNEditorNode_Method::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, UHTaskNetworkEditorPins::PinCategory_SingleComposite, TEXT("In"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, UHTaskNetworkEditorPins::PinCategory_SingleComposite, TEXT("Out"));
}

FText UHTNEditorNode_Method::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(Method->Name);
}

FText UHTNEditorNode_Method::GetTooltipText() const
{
	return FText();
}

void UHTNEditorNode_Method::AutowireNewNode(UEdGraphPin* FromPin)
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
