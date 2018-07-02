#pragma once

#include "LoginRequest.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FLoginRequest {

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Login")
		FString Email;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Login")
		FString RawPassword;

	FLoginRequest()
		: Email(FString())
		, RawPassword(FString())
	{
	};
};