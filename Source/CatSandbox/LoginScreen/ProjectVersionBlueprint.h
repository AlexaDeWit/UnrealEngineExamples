// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectVersionBlueprint.generated.h"

UCLASS()
class CATSANDBOX_API UProjectVersionBlueprint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Project Version", CompactNodeTitle = "ProjectVersion"), Category = "System Information")
		static FString GetProjectVersion();
	
};
