// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "AIGraph.h"
#include "HTaskNetworkEdGraph.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKEDITOR_API UHTaskNetworkEdGraph : public UAIGraph
{
	GENERATED_BODY()
public:
	virtual void UpdateAsset(int32 UpdateFlags) override;

private:
	void VisitCompound(class UHTNEditorNode_CompoundTask* CompoundTask);
	void VisitMethod(class UHTNEditorNode_Method* CompoundTask);
	class UHTNEditorNode_Root* FindRoot() const;
};


