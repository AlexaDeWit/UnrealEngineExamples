#pragma once

#include "CraftingSchematic.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FCraftingSchematic : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schematic Name")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schematic Description")
	FString Description;

	FCraftingSchematic()
		: Name(TEXT("Name"))
		, Description(TEXT("Description"))
	{}
};
