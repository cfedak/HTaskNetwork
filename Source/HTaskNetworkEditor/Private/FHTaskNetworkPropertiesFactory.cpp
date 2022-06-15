// Fill out your copyright notice in the Description page of Project Settings.


#include "FHTaskNetworkPropertiesFactory.h"
#include "HTaskNetworkEditor.h"

FHTaskNetworkPropertiesFactory::FHTaskNetworkPropertiesFactory(TSharedPtr<HTaskNetworkEditor> InEditor)
	:FWorkflowTabFactory(FName(TEXT("HTaskNetworkGraphProperty")), InEditor),
	 Editor(InEditor)
{
	TabLabel = FText::FromString(TEXT("Details"));
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");
	bIsSingleton = true;
	ViewMenuDescription = FText::FromString(TEXT("Details"));
	ViewMenuTooltip = FText::FromString(TEXT("Show the details view"));
}

FHTaskNetworkPropertiesFactory::~FHTaskNetworkPropertiesFactory()
{
}

TSharedRef<SWidget> FHTaskNetworkPropertiesFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(Editor.IsValid());
	return Editor.Pin()->SpawnProperties();
}

FText FHTaskNetworkPropertiesFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A TOOLTIP"));
}
