// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include <functional>
#include "GameFramework/GameModeBase.h"
#include "Character/CatSandboxCharacter.h"
#include "Player/CatSandboxPlayerController.h"
#include "../Http/Dto/JwtPayload.h"
#include "Http/HttpResponse.h"
#include "JwtService.h"
#include "CatSandboxGameMode.generated.h"


UCLASS(minimalapi)
class ACatSandboxGameMode : public AGameModeBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLoginDataDelegate, FUniqueNetIdRepl, PlayerNetId);
	

public:
	ACatSandboxGameMode();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FPlayerLoginDataDelegate PlayerDataReceivedDelegate;

	virtual void PreLogin(
		const FString & Options,
		const FString & Address,
		const FUniqueNetIdRepl & UniqueId,
		FString & ErrorMessage
	) override;

	virtual APlayerController* Login(
		UPlayer * NewPlayer,
		ENetRole InRemoteRole,
		const FString & Portal,
		const FString & Options,
		const FUniqueNetIdRepl & UniqueId,
		FString & ErrorMessage
	) override;


	virtual void Logout(AController* Existing) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	FTimerHandle PersistenceTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Persistence")
	void PersistPlayerStates();

	UFUNCTION(BlueprintCallable, Category = "Persistence")
	void PersistSingleCharacter(ACatSandboxCharacter* Character);

	void RegisterServerIP();

	FVector GetDefaultSpawnLocation();

  TMap<FUniqueNetIdRepl, FCharacterDto> CachedPlayerData;

protected:

  std::function<void(UHttpResponse *)> OnCharacterDataRetrieved(const FUniqueNetIdRepl & UniqueId);

	FString CheckConnectionValidity(const FString & Options, const FUniqueNetIdRepl & UniqueId, FJwtPayload & JwtBody);

	UPROPERTY(BlueprintReadOnly)
	AJwtService* JwtService;

  UPROPERTY(BlueprintReadOnly)
  FString ClientId = "asdfhkasjdfskdfs"; //Should be dynamic in future

  UPROPERTY(BlueprintReadOnly)
  FString ClientCredentials; //A self-signed jwt

};

