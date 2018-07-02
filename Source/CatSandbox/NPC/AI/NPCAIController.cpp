// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "Player/CatSandboxPlayerController.h"
#include "Globals/SandboxGameState.h"
#include "Interfaces/Targettable.h"
#include "NPCAIController.h"

bool ANPCAIController::ServerSendChatMessage_Validate(const FString & MessageText, EChatChannel Channel)
{
	return true;
}
void ANPCAIController::ServerSendChatMessage_Implementation(const FString & MessageText, EChatChannel Channel)
{
	ASandboxGameState* GameState = GetWorld() ? GetWorld()->GetGameState<ASandboxGameState>() : nullptr;
	if (GameState)
	{
		ITargettable* PlayerPawn = Cast<ITargettable>(GetPawn());
		if (PlayerPawn)
		{
			if (Channel == EChatChannel::ECC_Global)
			{
				GameState->MulticastReceiveMessage(PlayerPawn->Execute_GetDisplayName(GetPawn()), MessageText);
			}
			else
			{
				auto ThisPawn = GetPawn();
				auto playerIterator = GetWorld()->GetPlayerControllerIterator();
                for (; playerIterator; ++playerIterator)
				{
					auto con = (*playerIterator).Get();
					auto Controller = Cast<ACatSandboxPlayerController>(con);
					if (con && ThisPawn)
					{
						auto OtherPawn = Controller->GetPawn();
						if (OtherPawn && OtherPawn->GetHorizontalDistanceTo(ThisPawn) <= GameState->GetMaxChatDistance(Channel))
						{
							//OtherPawn->
							Controller->ClientReceiveChatMessage(MessageText, Channel, PlayerPawn->Execute_GetDisplayName(GetPawn()));
						}

					}
				}
			}
		}
	}
}


