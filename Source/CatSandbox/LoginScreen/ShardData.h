#pragma once

#include "ShardData.generated.h"

USTRUCT(BlueprintType)
struct FShardData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentIp;

	FShardData()
		: Name(FString())
		, CurrentIp(FString())
	{

	}
};
