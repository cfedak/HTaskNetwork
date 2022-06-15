#include "FAssetTypeActions_HTaskNetworkAsset.h"
#include "HTaskNetworkAsset.h"
#include "HTaskNetworkEditor.h"

void FAssetTypeActions_HTaskNetworkAsset::SetCategoryBit(EAssetTypeCategories::Type Bit)
{
	AssetCategoryBit = Bit;
}

FText FAssetTypeActions_HTaskNetworkAsset::GetName() const
{
	return FText::FromString(TEXT("Heirarchical Task Network"));
}

FColor FAssetTypeActions_HTaskNetworkAsset::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FAssetTypeActions_HTaskNetworkAsset::GetSupportedClass() const
{
	return UHTaskNetworkAsset::StaticClass();
}

void FAssetTypeActions_HTaskNetworkAsset::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto Object : InObjects)
	{
		auto NewAsset = Cast<UHTaskNetworkAsset>(Object);
		if (NewAsset != nullptr)
		{
			TSharedRef<HTaskNetworkEditor> NewEditor(new HTaskNetworkEditor());
			NewEditor->InitEditor(Mode, EditWithinLevelEditor, NewAsset);
		}
	}
}

uint32 FAssetTypeActions_HTaskNetworkAsset::GetCategories()
{
	return AssetCategoryBit;
}
