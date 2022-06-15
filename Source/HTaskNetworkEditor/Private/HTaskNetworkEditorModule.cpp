#include "HTaskNetworkEditorModule.h"
#include <IAssetTools.h>
#include "AssetToolsModule.h"
#include "FAssetTypeActions_HTaskNetworkAsset.h"
#include "GraphPanelNodeFactory_HTaskNetwork.h"

#define LOCTEXT_NAMESPACE "FHTaskNetworkEditorModule"

void FHTaskNetworkEditorModule::StartupModule()
{

	// Register Task Network Asset
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// Setup Category for Asset
	AssetCategoryBit = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("UserDefinedAsset")), LOCTEXT("UserDefinedAssetCategory", "User Defined Asset"));
	TSharedPtr<FAssetTypeActions_HTaskNetworkAsset> AssetTypeAction = MakeShareable(new FAssetTypeActions_HTaskNetworkAsset());
	AssetTypeAction->SetCategoryBit(AssetCategoryBit);

	// Perform the registration
	AssetToolsModule.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());
	TaskNetworkNodeFactory = MakeShareable(new FGraphPanelNodeFactory_HTaskNetwork());
	FEdGraphUtilities::RegisterVisualNodeFactory(TaskNetworkNodeFactory);
}

void FHTaskNetworkEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (TaskNetworkNodeFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(TaskNetworkNodeFactory);
		TaskNetworkNodeFactory.Reset();
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHTaskNetworkEditorModule, HTaskNetworkEditor)