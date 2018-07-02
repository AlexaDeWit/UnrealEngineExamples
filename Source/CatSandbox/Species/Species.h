#pragma once

#include "Species.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FSpecies : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString History;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPlayable;

	FSpecies()
		: Name(TEXT("Name"))
		, History(TEXT("Name"))
		, Description(TEXT("Name"))
		, IsPlayable(true)
		{}
};