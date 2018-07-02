// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PlayerController.h"
#include "Http/Dto/CharacterDto.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CATSANDBOX_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Connections")
	void ConnectToGameServerWithCharacterContextJwt(FString CharacterContextJwt);

	UPROPERTY(BlueprintReadWrite, Category = "Login")
	FString JwtBody;

};
