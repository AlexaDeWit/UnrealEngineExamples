// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "ProjectVersionBlueprint.h"

FString UProjectVersionBlueprint::GetProjectVersion() {

	FString ProjectVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);
	return ProjectVersion;
}


