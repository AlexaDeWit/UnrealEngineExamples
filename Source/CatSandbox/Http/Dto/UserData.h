#pragma once

#include "UserData.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FUserData {

	GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP|Authentication")
    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP|Authentication")
    FString Email;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP|Authentication")
    FString Username;

    FUserData()
        : Id(TEXT("UNKNOWN USER ID"))
        , Email(TEXT("Unknown"))
        , Username(TEXT("Unknown"))
        {
        };

};
