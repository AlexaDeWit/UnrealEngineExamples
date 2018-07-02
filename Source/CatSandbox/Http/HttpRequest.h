#pragma once

#include "Object.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpResponse.h"
#include "HttpRequest.generated.h"

UCLASS(BlueprintType, Blueprintable)
class CATSANDBOX_API UHttpRequest : public UObject
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHttpResponseDelegate, UHttpResponse*, Response);
    DECLARE_MULTICAST_DELEGATE_OneParam(FHttpResponseDelegateNonDynamic, UHttpResponse*);

public:

	UPROPERTY(BlueprintAssignable, Category = "Http|EventDispatchers")
		FHttpResponseDelegate OnResponseDelegate;

    FHttpResponseDelegateNonDynamic OnResponseReceivedDelegate;

	bool IsExpired();
	void Setup(TSharedPtr<IHttpRequest> internalRequest);

	UFUNCTION(BlueprintCallable, Category = "HTTP")
		void Send();

	UFUNCTION(BlueprintCallable, Category = "HTTP")
		UHttpRequest* WithHeader(FString headerName, FString headerValue);

	UFUNCTION(BlueprintCallable, Category = "HTTP")
		UHttpRequest* WithPayload(FString payload);


private:

	TSharedPtr<IHttpRequest> _internalRequest;

	void Resolve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	bool _isResolved = false;
};
