#pragma once

#include "ThreatTableEntry.generated.h"

USTRUCT(BlueprintType)
struct FThreatTableEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY()
	float ThreatLevel;

	FThreatTableEntry()
	{
		CombatTarget = nullptr;
		ThreatLevel = 0.f;
	}

	FThreatTableEntry(AActor* Target)
	{
		CombatTarget = Target;
		ThreatLevel = 0.f;
	}
};
