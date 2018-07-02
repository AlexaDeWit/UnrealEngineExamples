// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Globals/SandboxGameState.h"
#include "Character/CatSandboxCharacter.h"
#include "CatSandboxPlayerController.h"

ACatSandboxPlayerController::ACatSandboxPlayerController()
{
	bShowMouseCursor = true;
	bReplicates = true;
}

void ACatSandboxPlayerController::RegisterActionBinding(int KeySlot, FName ActionName)
{
	if (ActionBarAssignments.Contains(KeySlot))
	{
		ActionBarAssignments.Remove(KeySlot);
	}
	ActionBarAssignments.Add(KeySlot, ActionName);
}

void ACatSandboxPlayerController::UnregisterActionBinding(int KeySlot)
{
	if (ActionBarAssignments.Contains(KeySlot))
	{
		ActionBarAssignments.Remove(KeySlot);
	}
}

bool ACatSandboxPlayerController::ConfigurePawnFromPlayerState_Validate()
{
	return true;
}

void ACatSandboxPlayerController::ConfigurePawnFromPlayerState_Implementation()
{
  auto state = Cast<ASandboxPlayerState>(PlayerState);
  auto pawn = Cast<ACatSandboxCharacter>(GetPawn());
  if(state && pawn && state->HasReceivedCharacterData)
  {
    auto characterData = state->CharacterData;
    if(characterData.IsNewCharacter)
    {
      //New Character Setup login
    }
    else
    {
      //pawn->LoadinDatathing
    }
  }
}

void ACatSandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("MouseLookKey", IE_Pressed, this, &ACatSandboxPlayerController::OnMouseLookKeyPressed);
	InputComponent->BindAction("MouseLookKey", IE_Released, this, &ACatSandboxPlayerController::OnMouseLookKeyReleased);
	InputComponent->BindAction("SelectionKey", IE_Pressed, this, &ACatSandboxPlayerController::OnSelectionKeyPressed);
	InputComponent->BindAction("TogglePerformanceDisplay", IE_Pressed, this, &ACatSandboxPlayerController::OnPerformanceKeyPressed);
	InputComponent->BindAction("ToggleSkillBook", IE_Pressed, this, &ACatSandboxPlayerController::OnToggleSkillBookPressed);
	InputComponent->BindAction("ToggleProfessionsBrowser", IE_Pressed, this, &ACatSandboxPlayerController::OnToggleProfessionsBrowserPressed);
	InputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &ACatSandboxPlayerController::CameraZoomOut);
	InputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &ACatSandboxPlayerController::CameraZoomIn);
	InputComponent->BindAction("MouseLookKey", IE_Released, this, &ACatSandboxPlayerController::OnMouseLookKeyReleased);
	InputComponent->BindAction("ToggleEscapeMenu", IE_Released, this, &ACatSandboxPlayerController::OnEscapeMenuPressed);
	InputComponent->BindAxis("Turn", this, &ACatSandboxPlayerController::OnViewHorizontalAxis);
	InputComponent->BindAxis("LookUp", this, &ACatSandboxPlayerController::OnViewVerticalAxis);
	InputComponent->BindAction("ActionBarSlot1", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<1>);
	InputComponent->BindAction("ActionBarSlot2", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<2>);
	InputComponent->BindAction("ActionBarSlot3", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<3>);
	InputComponent->BindAction("ActionBarSlot4", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<4>);
	InputComponent->BindAction("ActionBarSlot5", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<5>);
	InputComponent->BindAction("ActionBarSlot6", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<6>);
	InputComponent->BindAction("ActionBarSlot7", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<7>);
	InputComponent->BindAction("ActionBarSlot8", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<8>);
	InputComponent->BindAction("ActionBarSlot9", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<9>);
	InputComponent->BindAction("ActionBarSlot10", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<10>);
	InputComponent->BindAction("ActionBarSlot11", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<11>);
	InputComponent->BindAction("ActionBarSlot12", IE_Pressed, this, &ACatSandboxPlayerController::ActionBarButtonPressed<12>);
}

void ACatSandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		if (Viewport)
		{
			LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
		}
	}
	if (IsLocalController() && RootWidgetClass)
	{
		RootWidget = CreateWidget<UUserWidget>(this, RootWidgetClass);
		if (RootWidget)
		{
			RootWidget->AddToViewport();
		}
	}
	SetInputMode(FInputModeGameAndUI());
}

void ACatSandboxPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (LookModeKeyHeld && ViewportSize.X && ViewportSize.Y)
	{
		GetLocalPlayer()->ViewportClient->Viewport->SetMouse(ViewportSize.X * 0.5f, ViewportSize.Y * 0.5f);
	}
}

void ACatSandboxPlayerController::Possess(APawn * aPawn)
{
	//Handle the "real" possession logic
	Super::Possess(aPawn);
	//Hook into the possess logic to apply player data.
	ConfigurePawnFromPlayerState();
}

void ACatSandboxPlayerController::OnMouseLookKeyPressed()
{
	bShowMouseCursor = false;
	LookModeKeyHeld = true;
}

void ACatSandboxPlayerController::OnMouseLookKeyReleased()
{
	bShowMouseCursor = true;
	LookModeKeyHeld = false;
}

void ACatSandboxPlayerController::OnSelectionKeyPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("LeftMouse!"));
	FHitResult SelectPoint;
	GetHitResultUnderCursor(ECC_Pawn, false, SelectPoint);
	if (SelectPoint.bBlockingHit && Cast<ITargettable>(SelectPoint.GetActor()) && SelectPoint.GetActor() != GetPawn())
	{
		if (SelectPoint.GetActor() != CurrentTarget)
		{
			ServerSetCurrentTarget(SelectPoint.GetActor());
		}
	}
	else
	{
		//Clear the target
		ServerSetCurrentTarget(nullptr);
	}
}

void ACatSandboxPlayerController::OnPerformanceKeyPressed()
{
	if (PerformanceDisplayKeyDelegate.IsBound())
	{
		PerformanceDisplayKeyDelegate.Broadcast();
	}
}

void ACatSandboxPlayerController::OnToggleSkillBookPressed()
{
	if (PlayerInputDelegate.IsBound())
	{
		PlayerInputDelegate.Broadcast(EInputAction::IA_ToggleSkillBook);
	}
}

void ACatSandboxPlayerController::OnToggleProfessionsBrowserPressed()
{
	if (PlayerInputDelegate.IsBound())
	{
		PlayerInputDelegate.Broadcast(EInputAction::IA_ToggleProfessionsBrowser);
	}
}

void ACatSandboxPlayerController::CameraZoomIn()
{
	ACatSandboxCharacter * pawn = Cast<ACatSandboxCharacter>(GetPawn());
	if (pawn)
	{
		pawn->GetCameraBoom()->TargetArmLength = FMath::Clamp(pawn->GetCameraBoom()->TargetArmLength - 15.f, 0.f, 1250.f);
		if (pawn->GetCameraBoom()->TargetArmLength < 100)
		{
			pawn->GetMesh()->SetOwnerNoSee(true);
		}
	}
}

void ACatSandboxPlayerController::CameraZoomOut()
{
	ACatSandboxCharacter * pawn = Cast<ACatSandboxCharacter>(GetPawn());
	if (pawn)
	{
		pawn->GetCameraBoom()->TargetArmLength = FMath::Clamp(pawn->GetCameraBoom()->TargetArmLength + 15.f, 0.f, 1250.f);
		if (pawn->GetCameraBoom()->TargetArmLength > 100)
		{
			pawn->GetMesh()->SetOwnerNoSee(false);
		}
	}
}

void ACatSandboxPlayerController::OnViewVerticalAxis(float y)
{
	if (LookModeKeyHeld)
	{
		AddPitchInput(y);
	}
}

void ACatSandboxPlayerController::OnViewHorizontalAxis(float x)
{
	if (LookModeKeyHeld)
	{
		AddYawInput(x);
	}
}

bool ACatSandboxPlayerController::ServerSetCurrentTarget_Validate(AActor * target)
{
	//Placeholder, range checking and stuff later probably.
	return true;
}

void ACatSandboxPlayerController::ServerSetCurrentTarget_Implementation(AActor * target)
{
	//Don't let nobody fuck it up!
	if (Cast<ITargettable>(target) || target == nullptr)
	{
		CurrentTarget = target;
	}
}

bool ACatSandboxPlayerController::ServerSendChatMessage_Validate(const FString & MessageText, EChatChannel Channel)
{
	return true;
}
void ACatSandboxPlayerController::ServerSendChatMessage_Implementation(const FString & MessageText, EChatChannel Channel)
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
						if (OtherPawn != ThisPawn && OtherPawn && OtherPawn->GetHorizontalDistanceTo(ThisPawn) <= GameState->GetMaxChatDistance(Channel))
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

AActor * ACatSandboxPlayerController::GetCurrentTarget()
{
	return CurrentTarget;
}
void ACatSandboxPlayerController::ActionBarButtonPressed(int32 Index)
{
	auto pawn = Cast<ISupportsCombat>(GetPawn());
	if (pawn)
	{
		if (ActionBarAssignments.Contains(Index))
		{
			auto ActionId = ActionBarAssignments[Index];
			if (CurrentTarget)
			{
				ISupportsCombat::Execute_ActivateAbility(GetPawn(), ActionId, CurrentTarget);
			}
		}
	}
}
void ACatSandboxPlayerController::OnRep_CurrentTarget()
{
	if (TargetChangedDelegate.IsBound())
	{
		TargetChangedDelegate.Broadcast(CurrentTarget);
	}
}
void ACatSandboxPlayerController::ClientReceiveChatMessage_Implementation(const FString & MessageText, EChatChannel Channel, const FName & SenderName)
{
	ASandboxGameState* GameState = GetWorld() ? GetWorld()->GetGameState<ASandboxGameState>() : nullptr;
	if (GameState)
	{
		if (GameState->ChatMessageReceivedDelegate.IsBound())
		{
			GameState->ChatMessageReceivedDelegate.Broadcast(SenderName, MessageText);
		}
	}
}
void ACatSandboxPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACatSandboxPlayerController, CurrentTarget);
}

void ACatSandboxPlayerController::OnEscapeMenuPressed() {
  if(PlayerInputDelegate.IsBound()){
    PlayerInputDelegate.Broadcast(EInputAction::IA_ToggleEscapeMenu);
  }
}
