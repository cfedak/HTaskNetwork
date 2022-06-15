#pragma once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"

struct FHTNGraphTabSummoner : public FDocumentTabFactoryForObjects<UEdGraph>
{
public:
	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);
	FHTNGraphTabSummoner(TSharedPtr<class HTaskNetworkEditor> InEditor, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);
	virtual ~FHTNGraphTabSummoner();

	virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;
	virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;
	virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* Editor) const;
protected:
	virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override;
	virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;

protected:
	TWeakPtr<HTaskNetworkEditor> Editor;
	FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;
};