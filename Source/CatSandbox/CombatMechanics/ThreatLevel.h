#pragma once

#include "Object.h"
#include "ThreatLevel.generated.h"

UCLASS(BlueprintType)
class UThreatLevel : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Threat")
	AActor* FromWho;

	UPROPERTY(BlueprintReadOnly, Category = "Threat")
	float ThreatAmount;
};
