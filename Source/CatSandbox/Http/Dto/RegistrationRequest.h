#pragma once

#include "RegistrationRequest.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FRequest_Registration {

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Registration")
		FString Email;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Registration")
		FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Registration")
		FString RawPassword;

	FRequest_Registration()
		: Email(FString())
		, Username(FString())
		, RawPassword(FString())
	{
	};
};