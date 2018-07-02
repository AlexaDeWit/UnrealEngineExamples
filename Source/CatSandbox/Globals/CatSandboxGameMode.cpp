// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "CatSandbox.h"
#include "CatSandboxGameMode.h"
#include "Runtime/Core/Public/Misc/DefaultValueHelper.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Http/HttpService.h"
#include "Player/SandboxPlayerState.h"
#include "Player/CatSandboxPlayerController.h"

#define THREE_MINUTES 180.f

ACatSandboxGameMode::ACatSandboxGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ACatSandboxPlayerController::StaticClass();
}

void ACatSandboxGameMode::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
  FJwtPayload JwtBody;
	FString connectOptionsCheckResult = CheckConnectionValidity(Options, UniqueId, JwtBody);
	if ( connectOptionsCheckResult != "")
	{
		ErrorMessage = ErrorMessage + connectOptionsCheckResult;
	}
  else
  {
    //Valid connection options
    auto httpService = AHttpService::GetInstance();
    auto req = httpService->GetCharacterData(ClientCredentials, JwtBody.CharacterId);
    req->OnResponseReceivedDelegate.AddLambda(OnCharacterDataRetrieved(UniqueId));
    req->Send();
  }
}

APlayerController * ACatSandboxGameMode::Login(
	UPlayer * NewPlayer,
	ENetRole InRemoteRole,
	const FString & Portal,
	const FString & Options,
	const FUniqueNetIdRepl & UniqueId,
	FString & ErrorMessage)
{
	APlayerController* initialPlayer = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
  auto state = Cast<ASandboxPlayerState>(initialPlayer->PlayerState);
  if(state)
  {
    auto data = CachedPlayerData.Find(UniqueId);
    if(data)
    {
      state->CharacterData = *data;
      state->HasReceivedCharacterData = true;
    }
  }
	return initialPlayer;
}

void ACatSandboxGameMode::Logout(AController * Existing)
{
	Super::Logout(Existing);
}

void ACatSandboxGameMode::BeginPlay()
{
	Super::BeginPlay();
	RegisterServerIP();
	GetWorldTimerManager().SetTimer(PersistenceTimerHandle, this, &ACatSandboxGameMode::PersistPlayerStates, THREE_MINUTES, true);
	JwtService = GetWorld()->SpawnActor<AJwtService>();
  ClientCredentials = JwtService->JwtFromClaims("{\"ClientId\":\"" + ClientId + "\", \"IsAuthoritativeGameServer\": true}");
}

void ACatSandboxGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACatSandboxGameMode::PersistPlayerStates()
{
}

void ACatSandboxGameMode::PersistSingleCharacter(ACatSandboxCharacter* Character)
{

}

void ACatSandboxGameMode::RegisterServerIP()
{

}

FVector ACatSandboxGameMode::GetDefaultSpawnLocation()
{
	//Temporary absolute value, to be replaced with registering spawn location data on a map by map basis.
	return FVector(-8930.0, 51594.0, 432.0);
}

FString ACatSandboxGameMode::CheckConnectionValidity(const FString & Options, const FUniqueNetIdRepl & UniqueId, FJwtPayload & JwtBody)
{
	//Validate all incoming connections If a connection lacks a session token, reject it outright. If one is present, callback to validation
	TArray<FString> outStrings;
	Options.ParseIntoArray(outStrings, TEXT("?"), true);
	FString rawJwt = "";
	for (auto &e : outStrings)
	{
		if (e.StartsWith("AuthorizationToken"))
		{
			FString left;
			e.Split("=", &left, &rawJwt);
		}
	}
	if (rawJwt != "")
	{
		//Validate and parse the JWT...
		if(JwtService->ParseJwtBody(rawJwt, JwtBody)) {
			//Accept the connection
			return FString("");
		} else {
			return FString("Invalid JWT Sent");
		}
	}
	else
	{
		//By returning a nonempty string, the user is kicked.
		return FString("Invalid Connection Options.");
	}
}


std::function<void(UHttpResponse *)> ACatSandboxGameMode::OnCharacterDataRetrieved(const FUniqueNetIdRepl & UniqueId)
{
  return [this, UniqueId](UHttpResponse * Response) {
    if(Response->WasSuccessful()) {
      bool wasSuccessful;
      FCharacterDto characterData;
      Response->ParseBodyToCharacterData(characterData, wasSuccessful);
      if(wasSuccessful) {
        CachedPlayerData.Add(UniqueId, characterData);
        if(PlayerDataReceivedDelegate.IsBound()) {
          PlayerDataReceivedDelegate.Broadcast(UniqueId);
        }
      }
    }
  };
}
