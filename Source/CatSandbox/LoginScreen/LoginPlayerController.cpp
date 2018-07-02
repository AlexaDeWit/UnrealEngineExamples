// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "LoginPlayerController.h"


void ALoginPlayerController::ConnectToGameServerWithCharacterContextJwt(FString CharacterContextJwt)
{
  FString ip = TEXT("127.0.0.1:7777");
  FString connectString = ip + "?AuthorizationToken=" + CharacterContextJwt;
	UE_LOG(LogTemp, Warning, TEXT("Setting payload: %s"), *connectString);
  ClientTravel(connectString, ETravelType::TRAVEL_Absolute);
}
