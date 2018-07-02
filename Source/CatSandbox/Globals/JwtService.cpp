#include "CatSandbox.h"
#include "JwtService.h"
#include "../Crypto/hmacsha256.h"
#include "../Crypto/base64.h"

AJwtService::AJwtService() { 
    PrimaryActorTick.bCanEverTick = true;
    int32 valueLength = 512;
    TCHAR* envVarValue = new TCHAR[valueLength];
#if PLATFORM_WINDOWS
    FWindowsPlatformMisc::GetEnvironmentVariable(TEXT("SECRET_JWT_KEY"), envVarValue, valueLength);
#endif
#if PLATFORM_LINUX
    FLinuxPlatformMisc::GetEnvironmentVariable(TEXT("SECRET_JWT_KEY"), envVarValue, valueLength);
#endif
#if PLATFORM_MAC
    FMacPlatformMisc::GetEnvironmentVariable(TEXT("SECRET_JWT_KEY"), envVarValue, valueLength);
#endif
    if(envVarValue[0] != 0){
        SecretKey = FString(envVarValue);
    } else {
        SecretKey = TEXT("ThisIsTotallyASecretKeyIPromise");
    }
}

bool AJwtService::ParseJwtBody(FString RawJwt, FJwtPayload & PayloadOut) {
    TArray<FString> outStrings;
    RawJwt.ParseIntoArray(outStrings, TEXT("."), true);
    if(outStrings.Num() < 3) return false;
    FString claims = outStrings[1];
    FString headerAndClaims = outStrings[0] + "." + claims;
    auto computedSignature = UHmacSha256::ComputeBase64Signature(headerAndClaims, SecretKey);
    if(computedSignature != outStrings[2]) return false;
    FString decodedClaims;
    if(!UBase64Codec::Base64UrlDecode(claims, decodedClaims)) return false;
    return FJsonObjectConverter::JsonObjectStringToUStruct<FJwtPayload>(decodedClaims, &PayloadOut, 0, 0);   
}

FString AJwtService::JwtFromClaims(FString Claims)
{
  FString RawHeader = "{\"typ\": \"JWT\", \"alg\": \"HS256\"}";
  FString EncodedHeader = UBase64Codec::Base64UrlEncode(RawHeader);
  FString EncodedClaims = UBase64Codec::Base64UrlEncode(Claims);
  FString Body = EncodedHeader + "." + EncodedClaims;
  FString Signature = UHmacSha256::ComputeBase64Signature(Body, SecretKey);
  return Body + "." + Signature;
}
