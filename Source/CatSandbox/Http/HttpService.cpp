#include "CatSandbox.h"
#include "HttpService.h"


AHttpService* AHttpService::instance = nullptr;

AHttpService::AHttpService() { PrimaryActorTick.bCanEverTick = true; }
void AHttpService::BeginPlay() {
	Super::BeginPlay();
	instance = this;
	Http = &FHttpModule::Get();
}

void AHttpService::Tick(float DeltaSeconds) {
	auto ToCull = TArray<UHttpRequest *>();
	for (auto req : PendingRequests) {
		if (req && req->IsExpired()) {
			ToCull.Add(req);
		}
	}
	//This pattern is so we don't trip on ourselves ever.
	for (auto req : ToCull) {
		PendingRequests.Remove(req);
	}
}

AHttpService * AHttpService::GetInstance()
{
	//For null-pointer safety guarantees...
	return Cast<AHttpService>(instance);
}

TSharedRef<IHttpRequest> AHttpService::RequestWithRoute(FString Subroute) {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetURL(ApiBaseUrl + Subroute);
	SetRequestHeaders(Request);
	return Request;
}

void AHttpService::SetRequestHeaders(TSharedRef<IHttpRequest>& Request) {
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
}

TSharedRef<IHttpRequest> AHttpService::GetRequest(FString Subroute) {
	UE_LOG(LogTemp, Warning, TEXT("Created Get Request To: %s"), *Subroute);
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest> AHttpService::PostRequest(FString Subroute, FString ContentJsonString) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	UE_LOG(LogTemp, Warning, TEXT("Setting payload: %s"), *ContentJsonString);
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

TSharedRef<IHttpRequest> AHttpService::DeleteRequest(FString Subroute) 
{
	UE_LOG(LogTemp, Warning, TEXT("Created Delete Request To: %s"), *Subroute);
  TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
  Request->SetVerb("DELETE");
  return Request;
}

bool AHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) return true;
	else {
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}

void AHttpService::SetClientAuthorizationHeader(FString ClientSecret, FString ClientId, TSharedRef<IHttpRequest>& Request)
{
  //TODO: Implement client credentials
}

void AHttpService::SetAuthorizationHash(FString JwtBody, TSharedRef<IHttpRequest>& Request) {
	Request->SetHeader(AuthorizationHeader, TEXT("Bearer ") + JwtBody);
}


/**************************************************************************************************************************/

template <typename StructType>
bool AHttpService::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput) {
	return FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename StructType>
bool AHttpService::GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput) {
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	return FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}

/**************************************************************************************************************************/




/************************************************************************************************************************/
/************************************************************************************************************************/
//											          REQUESTS
/************************************************************************************************************************/
/************************************************************************************************************************/

UHttpRequest * AHttpService::CreateAccount(FRequest_Registration Payload)
{
	FString JsonStringPayload;
	GetJsonStringFromStruct<FRequest_Registration>(Payload, JsonStringPayload);
	TSharedRef<IHttpRequest> Request = PostRequest("accounts/register", JsonStringPayload);
	auto req = NewObject<UHttpRequest>(this);
	req->Setup(Request);
	return req;
}

UHttpRequest * AHttpService::Login(FLoginRequest Payload)
{
	FString JsonStringPayload;
	GetJsonStringFromStruct<FLoginRequest>(Payload, JsonStringPayload);
	TSharedRef<IHttpRequest> Request = PostRequest("sessions/login", JsonStringPayload);
	auto req = NewObject<UHttpRequest>(this);
	req->Setup(Request);
	return req;
}

UHttpRequest * AHttpService::CreateCharacter(FCreateCharacterRequest Payload, FString JwtBody)
{
	FString JsonStringPayload;
	GetJsonStringFromStruct<FCreateCharacterRequest>(Payload, JsonStringPayload);
	TSharedRef<IHttpRequest> Request = PostRequest("characters/create", JsonStringPayload);
	SetAuthorizationHash(JwtBody, Request);
	auto req = NewObject<UHttpRequest>(this);
	req->Setup(Request);
	return req;
}

UHttpRequest * AHttpService::GetCharacterList(FString JwtBody)
{
	TSharedRef<IHttpRequest> Request = GetRequest("characters");
	SetAuthorizationHash(JwtBody, Request);
	auto req = NewObject<UHttpRequest>(this);
	req->Setup(Request);
	return req;
}

UHttpRequest* AHttpService::DeleteCharacter(FString JwtBody, FString CharacterId)
{
  TSharedRef<IHttpRequest> Request = DeleteRequest("characters/" + CharacterId);
  SetAuthorizationHash(JwtBody, Request);
  auto req = NewObject<UHttpRequest>(this);
  req->Setup(Request);
  return req;
}

UHttpRequest* AHttpService::ValidateCharacterContext(FString JwtBody, FString CharacterId)
{
  TSharedRef<IHttpRequest> Request = GetRequest("characters/validateCharacterContext/" + CharacterId);
  SetAuthorizationHash(JwtBody, Request);
  auto req = NewObject<UHttpRequest>(this);
  req->Setup(Request);
  return req;
}


// Game client requests
UHttpRequest* AHttpService::GetCharacterData(FString ClientJwt, FString CharacterId)
{
  TSharedRef<IHttpRequest> Request = GetRequest("private/characters/" + CharacterId);
  SetAuthorizationHash(ClientJwt, Request);
  auto req = NewObject<UHttpRequest>(this);
  req->Setup(Request);
  return req;
}
