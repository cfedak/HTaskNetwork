// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "HTaskNetworkFactory.generated.h"

/**
 * 
 */
UCLASS()
class HTASKNETWORKEDITOR_API UHTaskNetworkFactory : public UFactory
{
	GENERATED_BODY()
		UHTaskNetworkFactory();
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
};
