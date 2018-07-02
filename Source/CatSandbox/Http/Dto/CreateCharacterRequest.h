#pragma once

#include "CreateCharacterRequest.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FCreateCharacterRequest {

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		FString Species;

	FCreateCharacterRequest()
		: Name(TEXT("Unknown"))
		, Species(TEXT("Human"))
	{
	};
};