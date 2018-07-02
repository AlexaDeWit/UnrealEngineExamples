#pragma once
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Http/Dto/RegistrationRequest.h"
#include "Http/Dto/LoginRequest.h"
#include "Http/Dto/CreateCharacterRequest.h"
#include "HttpRequest.h"
#include "HttpService.generated.h"

UCLASS(Blueprintable, hideCategories = (Input))
class CATSANDBOX_API AHttpService : public AActor
{
	GENERATED_BODY()

private:
	FHttpModule* Http;

	FString ApiBaseUrl = "http://localhost:8080/api/";

	FString AuthorizationHeader = TEXT("Authorization");

	static AHttpService* instance;

	void SetClientAuthorizationHeader(FString ClientSecret, FString ClientId, TSharedRef<IHttpRequest>& Request);
	void SetAuthorizationHash(FString JwtBody, TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute);
	void SetRequestHeaders(TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString);
  TSharedRef<IHttpRequest> DeleteRequest(FString Subroute);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	template <typename StructType>
	bool GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	bool GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);

	UPROPERTY()
	TArray<UHttpRequest *> PendingRequests;

public:
	AHttpService();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "HTTP|Accounts")
		UHttpRequest* CreateAccount(FRequest_Registration Payload);

	UFUNCTION(BlueprintCallable, Category = "HTTP|Sessions")
		UHttpRequest* Login(FLoginRequest Payload);

	UFUNCTION(BlueprintCallable, Category = "HTTP|Characters")
		UHttpRequest* CreateCharacter(FCreateCharacterRequest Payload, FString JwtBody);

	UFUNCTION(BlueprintCallable, Category = "HTTP|Characters")
		UHttpRequest* GetCharacterList(FString JwtBody);

  UFUNCTION(BlueprintCallable, Category = "HTTP|Characters")
    UHttpRequest* DeleteCharacter(FString JwtBody, FString CharacterId);


  UFUNCTION(BlueprintCallable, Category = "HTTP|Characters")
    UHttpRequest* ValidateCharacterContext(FString JwtBody, FString CharacterId);

  //Game Client API Calls
  UFUNCTION(BlueprintCallable, Category = "HTTP|Characters")
    UHttpRequest* GetCharacterData(FString ClientJwt, FString CharacterId);

	virtual void Tick(float DeltaSeconds) override;

	//TODO: Make this take a world reference so it can spawn itself on the instance if not present
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HttpService")
		static AHttpService* GetInstance();
};
