// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "Player/Chat/ChatChannel.h"
#include "Http/HttpService.h"
#include "SandboxGameState.generated.h"

/**
 * 
 */
UCLASS()
class CATSANDBOX_API ASandboxGameState : public AGameStateBase
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChatMessageDelegate, FName, Sender, FString, Message);

public:

	static TMap<EChatChannel, int> ChatDistancesInitialiser();
	static const TMap<EChatChannel, int> ChatDistancesMap;

	UPROPERTY(BlueprintReadOnly)
	AHttpService* HttpServiceObj;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FChatMessageDelegate ChatMessageReceivedDelegate;
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastReceiveMessage(const FName & Sender, const FString & Message);

	UFUNCTION(BlueprintCallable, Category = "Chat")
	int GetMaxChatDistance(EChatChannel ForChannel);

protected:

	virtual void BeginPlay() override;
	
};
