// Fill out your copyright notice in the Description page of Project Settings.


#include "FAssetEditor_HTNGraph.h"

#define LOCTEXT_NAMESPACE "Editor_HTNGraph"

FAssetEditor_HTNGraph::FAssetEditor_HTNGraph()
{
}

FAssetEditor_HTNGraph::~FAssetEditor_HTNGraph()
{
}

FName FAssetEditor_HTNGraph::GetToolkitFName() const
{
    return TEXT("FHTNGraphEditor");
}

FText FAssetEditor_HTNGraph::GetBaseToolkitName() const
{
    return LOCTEXT("HTNGraphEditorAppLabel", "HTN Graph Editor");
}

FText FAssetEditor_HTNGraph::GetToolkitName() const
{
    return LOCTEXT("HTNGraphEditorToolkitName", "Some Graph Name");
}

FText FAssetEditor_HTNGraph::GetToolkitToolTipText() const
{
    //return FAssetEditorToolkit::GetToolTipTextForObject(this);
    return FText::FromString(TEXT("TODO TOOLTIP"));
}

FLinearColor FAssetEditor_HTNGraph::GetWorldCentricTabColorScale() const
{
    return FLinearColor::White;
}

FString FAssetEditor_HTNGraph::GetWorldCentricTabPrefix() const
{
    return TEXT("HTNGraphEditor");
}

FString FAssetEditor_HTNGraph::GetDocumentationLink() const
{
    return TEXT("");
}

void FAssetEditor_HTNGraph::SaveAsset_Execute()
{
    FAssetEditorToolkit::SaveAsset_Execute();
}

#undef LOCTEXT_NAMESPACE