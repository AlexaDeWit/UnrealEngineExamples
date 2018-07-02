// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Interfaces/Targettable.h"
#include "Player/Input/InputAction.h"
#include "Chat/ChatChannel.h"
#include "CatSandboxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CATSANDBOX_API ACatSandboxPlayerController : public APlayerController
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInputActionDelegate);

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDelegate, AActor*, NewTarget);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputDelegate, EInputAction, ActionTaken);

public:
	ACatSandboxPlayerController();
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FActorDelegate TargetChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FInputActionDelegate PerformanceDisplayKeyDelegate;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FInputDelegate PlayerInputDelegate;

	UFUNCTION(Server, Reliable, WithValidation, Category = "Setup")
	void ConfigurePawnFromPlayerState();

	UFUNCTION(BlueprintCallable, Category = "ActionBar")
	void RegisterActionBinding(int KeySlot, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category = "ActionBar")
	void UnregisterActionBinding(int KeySlot);

protected:

	//UMG Widget Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> RootWidgetClass;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
	UUserWidget* RootWidget;

	UPROPERTY(BlueprintReadOnly, Category = "ActionBar")
	TMap<int, FName> ActionBarAssignments;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	TArray<AActor*> CurrentCombatOpponents;

	bool LookModeKeyHeld = false;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

	virtual void Possess(APawn* aPawn) override;

	void OnMouseLookKeyPressed();
	void OnMouseLookKeyReleased();
	void OnSelectionKeyPressed();
	void OnPerformanceKeyPressed();
	void OnToggleSkillBookPressed();
	void OnToggleProfessionsBrowserPressed();
	void OnEscapeMenuPressed();

	void CameraZoomIn();
	void CameraZoomOut();

	void OnViewVerticalAxis(float y);
	void OnViewHorizontalAxis(float x);

	UPROPERTY(ReplicatedUsing=OnRep_CurrentTarget)
	AActor* CurrentTarget;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Targetting")
	void ServerSetCurrentTarget(AActor* target);

	UFUNCTION()
	void OnRep_CurrentTarget();

	FVector2D ViewportSize;

public:
	//Chat

	UFUNCTION(BlueprintCallable, Category = "Targetting")
	AActor* GetCurrentTarget();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Chat")
	void ServerSendChatMessage(const FString & MessageText, EChatChannel Channel);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Chat")
	void ClientReceiveChatMessage(const FString & MessageText, EChatChannel Channel, const FName & SenderName);

	void ActionBarButtonPressed(int32 Index);

	template<int32 Index>
	void ActionBarButtonPressed()
	{
		ActionBarButtonPressed(Index);
	};

	
};
