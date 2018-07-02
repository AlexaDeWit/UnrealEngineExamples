#pragma once

#include "Object.h"
#include "ThreatLevel.h"
#include "ThreatTable.generated.h"

UCLASS(BlueprintType)
class UThreatTable : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Threat")
	void ContributeThreat(AActor* FromWho, float ThreatValue);

	UFUNCTION(BlueprintCallable, Category = "Threat")
	UThreatLevel* FindThreatLevel(AActor* ForWhom);

	UFUNCTION(BlueprintCallable, Category = "Threat")
	UThreatLevel* FindTopThreat();

	UFUNCTION(BlueprintCallable, Category = "Threat")
	bool HasThreatTargets();

	UFUNCTION(BlueprintCallable, Category = "Threat")
	void ClearThreatTable();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Threat")
	TArray<UThreatLevel*> ThreatLevels = TArray<UThreatLevel*>();

};