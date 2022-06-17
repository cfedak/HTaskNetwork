// Fill out your copyright notice in the Description page of Project Settings.


#include "HTaskNetworkEdGraph.h"

#include "HTaskNetworkAsset.h"
#include "HTNEditorNode_CompoundTask.h"
#include "HTNEditorNode_Method.h"
#include "HTNEditorNode_PrimitiveTask.h"
#include "HTNEditorNode_Root.h"

void UHTaskNetworkEdGraph::UpdateAsset(int32 UpdateFlags)
{
	if (UHTaskNetworkAsset* Asset = CastChecked<UHTaskNetworkAsset>(GetOuter()))
	{
		// Clear existing data
		FTaskNetworkMethodChild NewRoot;
		Asset->RootNode = NewRoot;
		if (auto RootNode = FindRoot())
		{
			// We don't allow graph cycles, so just traverse the acyclic tree from the root.
			for (const auto Pin: RootNode->Pins)
			{
				if (Pin->Direction != EEdGraphPinDirection::EGPD_Output) { continue; }
				for (const auto ConnectedPin: Pin->LinkedTo)
				{
					const auto Node = ConnectedPin->GetOwningNode();
					if (const auto Compound = Cast<UHTNEditorNode_CompoundTask>(Node))
					{
						Asset->RootNode.CompoundChild = Compound->Task;
						VisitCompound(Compound);
					}
					else if (const auto Primitive = Cast<UHTNEditorNode_PrimitiveTask>(Node))
					{
						Asset->RootNode.PrimitiveChild = Primitive->Task;
					}
				}
			}
		}
	}
	Super::UpdateAsset(UpdateFlags);
}

UHTNEditorNode_Root* UHTaskNetworkEdGraph::FindRoot() const
{
	for(auto Node: Nodes)
	{
		if (auto RootNode = Cast<UHTNEditorNode_Root>(Node))
		{
			return RootNode;
		}
	}
	return nullptr;
}

void UHTaskNetworkEdGraph::VisitCompound(UHTNEditorNode_CompoundTask* CompoundTask)
{
	for (const auto Pin: CompoundTask->Pins)
	{
		if (Pin->Direction != EEdGraphPinDirection::EGPD_Output) { continue; }
		for (const auto ConnectedPin: Pin->LinkedTo)
		{
			auto VisitedNode = Cast<UHTNEditorNode_Method>(ConnectedPin->GetOwningNode());
			if (!VisitedNode) { continue; }
			CompoundTask->Task->Methods.AddUnique(VisitedNode->Method);

			VisitMethod(VisitedNode);
		}
	}
}

void UHTaskNetworkEdGraph::VisitMethod(UHTNEditorNode_Method* Method)
{
	Method->Method->SubTasks.Empty();
	for (const auto Pin: Method->Pins)
	{
		if (Pin->Direction != EEdGraphPinDirection::EGPD_Output) { continue; }
		for (const auto ConnectedPin: Pin->LinkedTo)
		{
			if (auto Compound = Cast<UHTNEditorNode_CompoundTask>(ConnectedPin->GetOwningNode()))
			{
				FTaskNetworkMethodChild Child;
				Child.CompoundChild = Compound->Task;
				Method->Method->SubTasks.Add(Child);
				VisitCompound(Compound);	
			}
			else if (auto Primitive = Cast<UHTNEditorNode_PrimitiveTask>(ConnectedPin->GetOwningNode()))
			{
				FTaskNetworkMethodChild Child;
				Child.PrimitiveChild = Primitive->Task;
				Method->Method->SubTasks.Add(Child);
			}
		}
	}
}
