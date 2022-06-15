// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNGraphApplicationMode.h"
#include "HTaskNetworkEditor.h"
#include "FHTaskNetworkPropertiesFactory.h"
#include "HTaskNetworkEditorTabs.h"

HTNGraphApplicationMode::HTNGraphApplicationMode(TSharedPtr<HTaskNetworkEditor> InEditor, FName InModeName)
	:FApplicationMode((TEXT("Graph"), TEXT("Graph Mode")))
{
	Editor = InEditor;

	TabFactories.RegisterFactory(MakeShareable(new FHTaskNetworkPropertiesFactory(InEditor)));

	TabLayout = FTabManager::NewLayout("Standalone_HTaskNetworkEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->AddTab(FHTaskNetworkGraphModeTabs::ViewportID, ETabState::ClosedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.2f)
					->AddTab(FHTaskNetworkGraphModeTabs::PropertyID, ETabState::OpenedTab)
				)
			)
		);
}

HTNGraphApplicationMode::~HTNGraphApplicationMode()
{
}

void HTNGraphApplicationMode::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager)
{
	check(Editor.IsValid());
	auto EditorApp = Editor.Pin();
	EditorApp->RegisterToolbarTab(InTabManager.ToSharedRef());
	EditorApp->PushTabFactories(TabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void HTNGraphApplicationMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void HTNGraphApplicationMode::PostActivateMode()
{
	check(Editor.IsValid());
	auto EditorApp = Editor.Pin();
	EditorApp->RestoreTaskNetwork();

	FApplicationMode::PostActivateMode();
}
