#include "FHTNGraphTabSummoner.h"
#include "HTaskNetworkEditor.h"
#include "HTaskNetworkEditorTabs.h"

FHTNGraphTabSummoner::FHTNGraphTabSummoner(TSharedPtr<HTaskNetworkEditor> InEditor, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback)
	:FDocumentTabFactoryForObjects<UEdGraph>(FHTaskNetworkGraphModeTabs::ViewportID, InEditor),
	Editor(InEditor),
	OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
}

FHTNGraphTabSummoner::~FHTNGraphTabSummoner()
{
}

void FHTNGraphTabSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(Editor.IsValid());
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	Editor.Pin()->OnGraphEditorFocused(GraphEditor);
}

void FHTNGraphTabSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
}

const FSlateBrush* FHTNGraphTabSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* InEditor) const
{
	return FEditorStyle::GetBrush(TEXT("GraphEditor.EventGraph_16x"));
}

TAttribute<FText> FHTNGraphTabSummoner::ConstructTabNameForObject(UEdGraph* DocumentID) const
{
	return TAttribute<FText>(FText::FromString(DocumentID->GetName()));
}

TSharedRef<SWidget> FHTNGraphTabSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}
