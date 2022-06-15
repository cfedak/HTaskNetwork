// Fill out your copyright notice in the Description page of Project Settings.


#include "HTaskNetworkFactory.h"
#include "HTaskNetworkAsset.h"

UHTaskNetworkFactory::UHTaskNetworkFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UHTaskNetworkAsset::StaticClass();
}


UObject* UHTaskNetworkFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UHTaskNetworkAsset::StaticClass()));
	return NewObject<UHTaskNetworkAsset>(InParent, Class, Name, Flags);
}

bool UHTaskNetworkFactory::CanCreateNew() const
{
	return true;
}
