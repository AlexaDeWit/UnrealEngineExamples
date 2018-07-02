#include "CatSandbox.h"
#include "HttpRequest.h"

bool UHttpRequest::IsExpired() {
	return _isResolved;
}

void UHttpRequest::Setup(TSharedPtr<IHttpRequest> internalRequest)
{
	_internalRequest = internalRequest;
	_internalRequest->OnProcessRequestComplete().BindUObject(this, &UHttpRequest::Resolve);
}

void UHttpRequest::Send()
{
	_internalRequest->ProcessRequest();
}

UHttpRequest* UHttpRequest::WithHeader(FString headerName, FString headerValue)
{
	return this;
}

UHttpRequest* UHttpRequest::WithPayload(FString payload)
{
	return this;
}

void UHttpRequest::Resolve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	auto response = NewObject<UHttpResponse>();
	response->Setup(Response, bWasSuccessful);
  if(OnResponseDelegate.IsBound())
  {
	  OnResponseDelegate.Broadcast(response);
  }
  if(OnResponseReceivedDelegate.IsBound())
  {
    OnResponseReceivedDelegate.Broadcast(response);
  }
	_isResolved = true;
}
