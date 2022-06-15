#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FHTaskNetworkEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	EAssetTypeCategories::Type AssetCategoryBit;

private:
	TSharedPtr<struct FGraphPanelNodeFactory> TaskNetworkNodeFactory;
};