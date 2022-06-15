// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

/**
 * 
 */
class HTASKNETWORKEDITOR_API FHTaskNetworkPropertiesFactory: public FWorkflowTabFactory
{
public:
	FHTaskNetworkPropertiesFactory(TSharedPtr<class HTaskNetworkEditor> InEditor);
	virtual ~FHTaskNetworkPropertiesFactory();

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<HTaskNetworkEditor> Editor;
};
