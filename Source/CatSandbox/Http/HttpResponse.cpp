#include "CatSandbox.h"
#include "HttpResponse.h"


void UHttpResponse::Setup(FHttpResponsePtr internalResponse, bool bWasSuccessful)
{
	_internalResponse = internalResponse;
	wasSuccessful = bWasSuccessful;
}

bool UHttpResponse::WasSuccessful()
{
	bool goodCode = false;
	switch (_internalResponse->GetResponseCode())
	{
		//Fall through all good codes intentionally.
	case 200:
	case 201:
	case 202:
	case 203:
	case 204:
	case 205:
	case 206:
	case 207:
	case 208:
	case 226:
		goodCode = true;
		break;
	default:
		goodCode = false;
		break;
	}
	return wasSuccessful && goodCode;
}

template <typename StructType>
void UHttpResponse::GetParsedBody(StructType& StructOutput, bool& bWasSuccessFul)
{
	FString JsonString = _internalResponse->GetContentAsString();
	bWasSuccessFul = FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}

template <typename StructType>
void UHttpResponse::GetArrayBody(TArray<StructType> & ArrayOutput, bool& bWasSuccessful)
{
	FString JsonString = _internalResponse->GetContentAsString();
	bWasSuccessful = FJsonObjectConverter::JsonArrayStringToUStruct<StructType>(JsonString, &ArrayOutput, 0, 0);
}

FString UHttpResponse::RawResponseBody()
{
  return _internalResponse->GetContentAsString();
}

/*******************************************************************************

						RESPONSE PARSERS
	

********************************************************************************/

void UHttpResponse::ParseBodyToCharacterList(TArray<FCharacterDto> & ArrayOutput, bool& bWasSuccessful)
{
	GetArrayBody(ArrayOutput, bWasSuccessful);
}

void UHttpResponse::ParseBodyToCharacterData(FCharacterDto & CharacterOut, bool & bWasSuccessful)
{
  GetParsedBody<FCharacterDto>(CharacterOut, bWasSuccessful);
}
