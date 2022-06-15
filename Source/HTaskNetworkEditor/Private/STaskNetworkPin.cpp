// Fill out your copyright notice in the Description page of Project Settings.


#include "STaskNetworkPin.h"


void STaskNetworkPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SGraphPinAI::Construct(SGraphPinAI::FArguments(), InPin);
}

FSlateColor STaskNetworkPin::GetPinColor() const
{
	return FSlateColor(FColor::Red);
}
