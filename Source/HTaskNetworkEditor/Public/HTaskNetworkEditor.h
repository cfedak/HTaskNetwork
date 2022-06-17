// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGraphEditor.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

/**
 * 
 */
class HTASKNETWORKEDITOR_API HTaskNetworkEditor: 
	public FWorkflowCentricApplication, 
	public FAIGraphEditor, 
	public FNotifyHook
{
public:
	HTaskNetworkEditor();
	~HTaskNetworkEditor();

	// -- FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	// --

	// -- FWorkflowCentricApplication interface
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject);
	// -- FWorkflowCentricApplication interface

	// Tabs
	TSharedRef<SWidget> SpawnProperties();

	// Documents
	void RestoreTaskNetwork();
	bool InEditingMode(bool GraphIsEditable) const;
	FGraphAppearanceInfo GetGraphAppearance() const;

	// hack copied from BT Editor
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);

	// Events
	void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& GraphEditor);

protected:
	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);
private:
	void CreateInternalWidgets();
	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);

	TSharedPtr<class IDetailsView> DetailsView;
	TSharedPtr<class FDocumentTracker> DocumentManager;

	class UHTaskNetworkAsset* TaskNetwork;
	TSharedPtr<FUICommandList> AdditionalEditorCommands; 
};
