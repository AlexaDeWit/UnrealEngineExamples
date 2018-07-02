#pragma once

#include "GameFramework/PlayerState.h"
#include "Http/Dto/CharacterDto.h"
#include "SandboxPlayerState.generated.h"

UCLASS()

class CATSANDBOX_API ASandboxPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Http|Character")
	FCharacterDto CharacterData;

  UPROPERTY(BlueprintReadOnly, Replicated, Category = "Http|Character")
  bool HasReceivedCharacterData;

	virtual void BeginPlay() override;

	UFUNCTION(Category = "DelegateHandlers")
	void OnNotifyPlayerDataAvailable(FUniqueNetIdRepl PlayerUniqueId);
	

};
