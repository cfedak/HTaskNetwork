// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HTASKNETWORKEDITOR_API FAssetEditor_HTNGraph: public FAssetEditorToolkit, public FGCObject
{
public:
	FAssetEditor_HTNGraph();
	virtual ~FAssetEditor_HTNGraph();

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void SaveAsset_Execute() override;
	// End of FAssetEditorToolkit
};
