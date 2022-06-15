// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EdGraph/EdGraphPin.h"
#include "HTaskNetworkEditorPins.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKEDITOR_API UHTaskNetworkEditorPins : public UObject
{
	GENERATED_BODY()
	
public:
	static const FName PinCategory_SingleTask;
	static const FName PinCategory_SingleComposite;
	static const FName PinCategory_MultipleMethods;
	static const FName PinCategory_MultipleTasks;
};
