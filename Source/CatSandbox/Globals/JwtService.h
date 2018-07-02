#pragma once

#include "../Http/Dto/JwtPayload.h"
#include "JsonUtilities.h"
#include "JwtService.generated.h"

UCLASS(Blueprintable, hideCategories = (Input))
class CATSANDBOX_API AJwtService : public AActor
{
	GENERATED_BODY()

	public:
	AJwtService();

  UFUNCTION(BlueprintCallable, Category = "Authentication")
  bool ParseJwtBody(FString RawJwt, FJwtPayload & PayloadOut);

  UFUNCTION(BlueprintCallable, Category = "Authentication")
  FString JwtFromClaims(FString Claims);

	private:
	FString SecretKey;
};
