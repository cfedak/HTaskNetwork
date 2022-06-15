#pragma once
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_HTaskNetworkAsset : public FAssetTypeActions_Base
{
public:
	void SetCategoryBit(EAssetTypeCategories::Type Bit);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

protected:
	EAssetTypeCategories::Type AssetCategoryBit;
};
