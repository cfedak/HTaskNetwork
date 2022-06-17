// Fill out your copyright notice in the Description page of Project Settings.


#include "HTaskNetworkEditor.h"
#include "Framework/Commands/GenericCommands.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "FHTNGraphTabSummoner.h"
#include "HTNGraphApplicationMode.h"
#include "HTaskNetworkEdGraph.h"
#include "EdGraphSchema_HTaskNetwork.h"
#include "IDetailsView.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "HTNEditorNode_CompoundTask.h"
#include "HTNEditorNode_PrimitiveTask.h"
#include "HTaskNetworkAsset.h"
#include "HTNEditorNode_Method.h"

#define LOCTEXT_NAMESPACE "FHTaskNetworkEditorModule"

const FName HTaskNetworkEditorAppIdentifier = FName(TEXT("HTaskNetworkEditorApp"));

HTaskNetworkEditor::HTaskNetworkEditor()
{
}

HTaskNetworkEditor::~HTaskNetworkEditor()
{
}

FName HTaskNetworkEditor::GetToolkitFName() const
{
    return TEXT("Heirarchical Task Network");
}

FText HTaskNetworkEditor::GetBaseToolkitName() const
{
    return FText::FromString(TEXT("Heirarchical Task Network BaseTKName"));
}

FText HTaskNetworkEditor::GetToolkitName() const
{
    return FText::FromString(TEXT("Heirarchical Task Network TKName"));
}

FText HTaskNetworkEditor::GetToolkitToolTipText() const
{
    return FText();
}

FLinearColor HTaskNetworkEditor::GetWorldCentricTabColorScale() const
{
    return FLinearColor::White;
}

FString HTaskNetworkEditor::GetWorldCentricTabPrefix() const
{
    return TEXT("HTN");
}

void HTaskNetworkEditor::RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

void HTaskNetworkEditor::OnGraphEditorFocused(const TSharedRef<SGraphEditor>& GraphEditor)
{
	UpdateGraphEdPtr = GraphEditor;
}

bool HTaskNetworkEditor::InEditingMode(bool GraphIsEditable) const
{
	return GraphIsEditable;
}

FGraphAppearanceInfo HTaskNetworkEditor::GetGraphAppearance() const
{
	return FGraphAppearanceInfo();
}

void HTaskNetworkEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	DocumentManager->SetTabManager(InTabManager);

	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void HTaskNetworkEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	UHTaskNetworkAsset* TaskNetworkToEdit = Cast<UHTaskNetworkAsset>(InObject);
	TaskNetwork = TaskNetworkToEdit;

    FGenericCommands::Register();

	TSharedPtr<HTaskNetworkEditor> ThisPtr(SharedThis(this));
	if (!DocumentManager.IsValid())
	{
		DocumentManager = MakeShareable(new FDocumentTracker());
		DocumentManager->Initialize(ThisPtr);
		TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FHTNGraphTabSummoner(ThisPtr,
			FHTNGraphTabSummoner::FOnCreateGraphEditorWidget::CreateSP(this, &HTaskNetworkEditor::CreateGraphEditorWidget)));
		DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
	}

    CreateInternalWidgets();

	const bool CreateDefaultStandaloneMenu = true;
	const bool CreateDefaultToolbar = true;
    FAssetEditorToolkit::InitAssetEditor(Mode, 
		InitToolkitHost, 
		HTaskNetworkEditorAppIdentifier, 
		FTabManager::FLayout::NullLayout, 
		CreateDefaultStandaloneMenu, 
		CreateDefaultToolbar, 
		InObject);

    AddApplicationMode(
        TEXT("Graph"),
        MakeShareable(new HTNGraphApplicationMode(SharedThis(this), TEXT("Graph"))));
    SetCurrentMode(TEXT("Graph"));
}

TSharedRef<SWidget> HTaskNetworkEditor::SpawnProperties()
{
    return SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .FillHeight(1.0f)
        .HAlign(HAlign_Fill)
        [
            DetailsView.ToSharedRef()
        ];
}

void HTaskNetworkEditor::RestoreTaskNetwork()
{
	UHTaskNetworkEdGraph* Graph = Cast<UHTaskNetworkEdGraph>(TaskNetwork->HTNGraph);
	const bool IsNewGraph = Graph == NULL;
	if (IsNewGraph)
	{
		// create a new Graph editor
		Graph = Cast<UHTaskNetworkEdGraph>(
			FBlueprintEditorUtils::CreateNewGraph(TaskNetwork,
				TEXT("Task Network"),
				UHTaskNetworkEdGraph::StaticClass(),
				UEdGraphSchema_HTaskNetwork::StaticClass()));
		TaskNetwork->HTNGraph = Graph;
		auto Schema = Graph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*Graph);
	}
	
	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(Graph);
	TSharedPtr<SDockTab> DocumentTab = DocumentManager->OpenDocument(Payload, FDocumentTracker::RestorePreviousDocument);
}

void HTaskNetworkEditor::OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)
{
	UE_LOG(LogTemp, Log, TEXT("%s: Start"), *FString(__FUNCTION__));

	TArray<UObject*> DetailsObjects;
	for (auto Object : NewSelection.Array())
	{
		if (const UHTNEditorNode_CompoundTask* Compound = Cast<UHTNEditorNode_CompoundTask>(Object))
		{
			DetailsObjects.Add(Compound->Task);
		}
		else if (const UHTNEditorNode_PrimitiveTask* Primitive = Cast<UHTNEditorNode_PrimitiveTask>(Object))
		{
			DetailsObjects.Add(Primitive->Task);
		}
		else if (const UHTNEditorNode_Method* Method = Cast<UHTNEditorNode_Method>(Object))
		{
			DetailsObjects.Add(Method->Method);
		}
	}
	if (DetailsObjects.Num() == 1)
	{
		if (DetailsView.IsValid())
		{
			DetailsView->SetObjects(DetailsObjects);
		}
	}
	else if (DetailsView.IsValid())
	{
		DetailsView->SetObject(nullptr);
	}
}

void HTaskNetworkEditor::CreateInternalWidgets()
{
    FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs; //(false, false, true, FDetailsViewArgs::HideNameArea, false);
    DetailsViewArgs.NotifyHook = this;
    DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
    DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    DetailsView->SetObject(nullptr);
    //DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateSP(this, &HTaskNetworkEditor::IsPropertyEditable));
    //DetailsView->OnFinishedChangingProperties().AddSP(this, &HTaskNetworkEditor::OnFinishedChangingProperties);
}

TSharedRef<SGraphEditor> HTaskNetworkEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);
	CreateCommandList();
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &HTaskNetworkEditor::OnSelectedNodesChanged);
	//InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FTestEditor::OnNodeDoubleClicked);
	//InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FTestEditor::OnNodeTitleCommitted);

	// Make title bar
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush(TEXT("Graph.TitleBackground")))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("TestGraphLabel", "HTNGraph"))
			.TextStyle(FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
			]
		];

	// Make full graph editor
	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
		// Bind commands in GraphEditorCommands.  Many are bound by superclass.
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(this, &HTaskNetworkEditor::InEditingMode, bGraphIsEditable)
		.Appearance(this, &HTaskNetworkEditor::GetGraphAppearance)
		.TitleBar(TitleBarWidget)
		.GraphToEdit(InGraph)
		.GraphEvents(InEvents);
}

#undef LOCTEXT_NAMESPACE