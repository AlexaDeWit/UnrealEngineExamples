#pragma once

#include "Personality.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FPersonality : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> IdleMessages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> CombatMessages;

	FPersonality()
	{}
};
