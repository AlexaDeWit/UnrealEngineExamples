#include "CatSandbox.h"
#include "Globals/CatSandboxGameMode.h"
#include "SandboxPlayerState.h"


void ASandboxPlayerState::BeginPlay()
{
	Super::BeginPlay();
	auto GameMode = Cast<ACatSandboxGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->PlayerDataReceivedDelegate.AddDynamic(this, &ASandboxPlayerState::OnNotifyPlayerDataAvailable);
	}
}

void ASandboxPlayerState::OnNotifyPlayerDataAvailable(FUniqueNetIdRepl PlayerUniqueId)
{
  auto GameMode = Cast<ACatSandboxGameMode>(GetWorld()->GetAuthGameMode());
  if(GameMode)
  {
    if(PlayerUniqueId == UniqueId)
    {
      GameMode->PlayerDataReceivedDelegate.RemoveDynamic(this, &ASandboxPlayerState::OnNotifyPlayerDataAvailable);
      auto controller = Cast<ACatSandboxPlayerController>(GetOwner());
      if(controller)
      {
        auto data = GameMode->CachedPlayerData.Find(UniqueId);
        if(data)
        {
          HasReceivedCharacterData = true;
          CharacterData = *data;
        }
      }
    }
  }
}



void ASandboxPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const

{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ASandboxPlayerState, CharacterData, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ASandboxPlayerState, HasReceivedCharacterData, COND_OwnerOnly);

}
