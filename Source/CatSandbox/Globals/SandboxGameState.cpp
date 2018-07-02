// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "SandboxGameState.h"

const TMap<EChatChannel, int> ASandboxGameState::ChatDistancesMap = ASandboxGameState::ChatDistancesInitialiser();

void ASandboxGameState::BeginPlay()
{
	Super::BeginPlay();
	HttpServiceObj = GetWorld()->SpawnActor<AHttpService>();
}
void ASandboxGameState::MulticastReceiveMessage_Implementation(const FName & Sender, const FString & Message)
{
	if (ChatMessageReceivedDelegate.IsBound())
	{
		ChatMessageReceivedDelegate.Broadcast(Sender, Message);
	}
}

TMap<EChatChannel, int> ASandboxGameState::ChatDistancesInitialiser()
{
	auto distances = TMap<EChatChannel, int>();
	distances.Add(EChatChannel::ECC_Say, 5000);
	distances.Add(EChatChannel::ECC_Yell, 15000);
	distances.Add(EChatChannel::ECC_NPCSay, 1500);
	return distances;
}

int ASandboxGameState::GetMaxChatDistance(EChatChannel ForChannel)
{
	return ASandboxGameState::ChatDistancesMap.Contains(ForChannel) ? *ASandboxGameState::ChatDistancesMap.Find(ForChannel) : 0;
}
