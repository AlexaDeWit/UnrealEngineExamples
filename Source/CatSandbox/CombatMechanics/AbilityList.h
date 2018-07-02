#pragma once

#include "AbilityList.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FAbilityList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> AbilityIds;

};
