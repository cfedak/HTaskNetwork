// Fill out your copyright notice in the Description page of Project Settings.


#include "EdGraphSchema_HTaskNetwork.h"
#include "HTNEditorNode_CompoundTask.h"
#include "HTNEditorNode_PrimitiveTask.h"
#include "HTNEditorNode_Method.h"
#include "HTaskNetworkCycleChecker.h"
#include "HTaskNetworkEditorPins.h"
#include "HTNEditorNode_Root.h"

#define LOCTEXT_NAMESPACE "FHTaskNetworkEditorModule"

const FPinConnectionResponse UEdGraphSchema_HTaskNetwork::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode", "Both are on the same node"));
	}
	FHTaskNetworkCycleChecker Checker;
	if (!Checker.CheckForLoop(A->GetOwningNode(), B->GetOwningNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorCycle", "Can't create a graph cycle"));
	}
	// Make sure the pins are not on the same node
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
}

void UEdGraphSchema_HTaskNetwork::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UHTNEditorNode_Root> Creator(Graph);
	auto NewNode = Creator.CreateNode();
	Creator.Finalize();
}

void UEdGraphSchema_HTaskNetwork::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	const FName PinCategory = ContextMenuBuilder.FromPin ?
		ContextMenuBuilder.FromPin->PinType.PinCategory : 
		UHTaskNetworkEditorPins::PinCategory_SingleComposite;
	
	if (PinCategory.IsEqual(UHTaskNetworkEditorPins::PinCategory_MultipleMethods))
	{
		const auto MethodAction = MakeShared<FEdGraphSchemaAction_NewNode>(FText::FromString(TEXT("")),
			FText::FromString(TEXT("Method")), FText(), 0);
		MethodAction->NodeTemplate = NewObject<UHTNEditorNode_Method>();
		ContextMenuBuilder.AddAction(MethodAction);
	}
	else
	{
		const auto CompoundAction = MakeShared<FEdGraphSchemaAction_NewNode>(
			FText::FromString(TEXT("")), FText::FromString(TEXT("Compound Task")),
			FText(), 0);
		CompoundAction->NodeTemplate = NewObject<UHTNEditorNode_CompoundTask>();
		const auto PrimitiveAction = MakeShared<FEdGraphSchemaAction_NewNode>(
			FText::FromString(TEXT("")), FText::FromString(TEXT("Primitive Task")),
			FText(), 0);
		PrimitiveAction->NodeTemplate = NewObject<UHTNEditorNode_PrimitiveTask>();

		ContextMenuBuilder.AddAction(CompoundAction);
		ContextMenuBuilder.AddAction(PrimitiveAction);
	}
}

#undef LOCTEXT_NAMESPACE
