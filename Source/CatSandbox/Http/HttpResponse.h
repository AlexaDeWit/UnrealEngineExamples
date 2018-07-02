#pragma once

#include "Object.h"
#include "Dto/CharacterDto.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpResponse.generated.h"

UCLASS(BlueprintType, Blueprintable)
class CATSANDBOX_API UHttpResponse : public UObject
{
	GENERATED_BODY()

public:

		void Setup(FHttpResponsePtr internalResponse, bool bWasSuccessful);

		UFUNCTION(BlueprintCallable, Category = "Http")
			bool WasSuccessful();

		template <typename StructType>
		void GetParsedBody(StructType& StructOutput, bool& bWasSuccessFul);

		template <typename StructType>
		void GetArrayBody(TArray<StructType> & ArrayOutput, bool& bWasSuccessful);

    UFUNCTION(BlueprintCallable, Category = "Http")
      FString RawResponseBody();

		/* Response Parsers For Blueprint */
		UFUNCTION(BlueprintCallable, Category = "Http|Parsers")
			void ParseBodyToCharacterList(TArray<FCharacterDto>& ArrayOutput, bool& bWasSuccessful);

		UFUNCTION(BlueprintCallable, Category = "Http|Parsers")
      void ParseBodyToCharacterData(FCharacterDto & CharacterOut, bool & bWasSuccessful);
private:
	
	FHttpResponsePtr _internalResponse;
	bool wasSuccessful = false;

};
