// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/**
 * 
 */
class HTASKNETWORKEDITOR_API HTNGraphApplicationMode : public FApplicationMode
{
public:
	HTNGraphApplicationMode(TSharedPtr<class HTaskNetworkEditor> InEditor, FName InModeName);
	virtual ~HTNGraphApplicationMode();

	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:
	TWeakPtr<HTaskNetworkEditor> Editor;
	FWorkflowAllowedTabSet TabFactories;
};
