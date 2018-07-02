#pragma once

#include "UserData.h"
#include "JwtPayload.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FJwtPayload {

	GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP|Authentication")
    FUserData UserData;

    long Expiry; //Timestamp

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP|Authentication")
    FString CharacterId;

    FJwtPayload()
        : UserData(FUserData())
        , Expiry(0) //Won't really do anything because not a UPROPERTY
        , CharacterId(TEXT("CHARACTER ID NOT RESOLVED"))
        {
        };

};
