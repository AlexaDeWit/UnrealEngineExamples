// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Player/Chat/ChatChannel.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class CATSANDBOX_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//Chat
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Chat")
	void ServerSendChatMessage(const FString & MessageText, EChatChannel Channel);
	
	
};
