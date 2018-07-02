// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "CatSandbox.h"
#include "CombatMechanics/ActionData.h"
#include "Globals/CatSandboxGameMode.h"
#include "CatSandboxCharacter.h"


//////////////////////////////////////////////////////////////////////////
// ACatSandboxCharacter

ACatSandboxCharacter::ACatSandboxCharacter() : Super()
{

	// set our turn rates for input
	BaseTurnRate = 450.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 5400.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxAcceleration = 20000;
	GetCharacterMovement()->AirControl = 0.03f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 55.f);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	NavInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("NavInvoker"));
}

void ACatSandboxCharacter::PrintMessageToScreen(FString Text)
{
	GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, Text);
}

void ACatSandboxCharacter::UnPossessed()
{
	auto GameMode = Cast<ACatSandboxGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->PersistSingleCharacter(this);
	}
}

bool ACatSandboxCharacter::GetIsInitialised()
{
	return IsInitialised;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACatSandboxCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACatSandboxCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACatSandboxCharacter::MoveRight);

}

void ACatSandboxCharacter::RPCActivateAbility_Implementation(FName AbilityName, AActor* Target)
{
	auto abilityStruct = AbilityData->FindRow<FActionData>(AbilityName, "Look up ability for activation by character");
	auto abilityClass = abilityStruct->ActionTaken.Get();
	if (!abilityClass)
	{
		return;
	}
	auto ability = NewObject<UCombatAction>(this, abilityClass);
	if (!ability)
	{
		return;
	}
	//We reliably get this far. Something after this is derping and not resulting in combat behaviour or damage taken
	ability->SetTarget(Target);
	ability->SetMaxRange(abilityStruct->MaxRange);
	ability->SetInstigationData(this, GetController());
	ability->ActivateAbility();
}

bool ACatSandboxCharacter::RPCActivateAbility_Validate(FName AbilityName, AActor* Target)
{
	//Include disconnect-related validation here
	return true;
}


void ACatSandboxCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACatSandboxCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACatSandboxCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACatSandboxCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


	//---Current stats---

 //Primary

float ACatSandboxCharacter::GetCurrentHP_Implementation()
{
	return CurrentHealth;
}

float ACatSandboxCharacter::GetCurrentHealthWounds()
{
	return CurrentHealthWounds;
}

float ACatSandboxCharacter::GetCurrentStamina_Implementation()
{
	return CurrentStamina;
}

float ACatSandboxCharacter::GetCurrentStaminaWounds()
{
	return CurrentStaminaWounds;
}

float ACatSandboxCharacter::GetCurrentFocus_Implementation()
{
	return CurrentFocus;
}

float ACatSandboxCharacter::GetCurrentFocusWounds()
{
	return CurrentFocusWounds;
}
	//---Secondary---

//Health
float ACatSandboxCharacter::GetCurrentToughness()
{
	return CurrentToughness;
}

float ACatSandboxCharacter::GetCurrentToughnessWounds()
{
	return CurrentToughnessWounds;
}

float ACatSandboxCharacter::GetCurrentConstitution()
{
	return CurrentConstitution;
}

float ACatSandboxCharacter::GetCurrentConstitutionWounds()
{
	return CurrentConstitutionWounds;
}
//Stamina

float ACatSandboxCharacter::GetCurrentEndurance()
{
	return CurrentEndurance;
}

float ACatSandboxCharacter::GetCurrentEnduranceWounds()
{
	return CurrentEnduranceWounds;
}

float ACatSandboxCharacter::GetCurrentQuickness()
{
	return CurrentQuickness;
}

float ACatSandboxCharacter::GetCurrentQuicknessWounds()
{
	return CurrentQuicknessWounds;
}

//Focus

float ACatSandboxCharacter::GetCurrentClarity()
{
	return CurrentClarity;
}

float ACatSandboxCharacter::GetCurrentClarityWounds()
{
	return CurrentClarityWounds;
}

float ACatSandboxCharacter::GetCurrentWillpower()
{
	return CurrentWillpower;
}

float ACatSandboxCharacter::GetCurrentWillpowerWounds()
{
	return CurrentWillpowerWounds;
}
	//---Max stats---
 
 //Primary

float ACatSandboxCharacter::GetMaxHP_Implementation()
{
	return BaseHealth;
}

float ACatSandboxCharacter::GetMaxStamina_Implementation()
{
	return BaseStamina;
}

float ACatSandboxCharacter::GetMaxFocus_Implementation()
{
	return BaseFocus;
}

	//---Secondary---

//Health

float ACatSandboxCharacter::GetMaxToughness()
{
	return BaseToughness;
}


float ACatSandboxCharacter::GetTotalMaxToughness()
{
	return BaseToughness - CurrentConstitutionWounds;
}

float ACatSandboxCharacter::GetMaxConstitution()
{
	return BaseConstitution;
}

float ACatSandboxCharacter::GetTotalMaxConstitution()
{
	return BaseConstitution - CurrentConstitutionWounds;
}

//Stamina

float ACatSandboxCharacter::GetMaxEndurance()
{
	return BaseEndurance;
}


float ACatSandboxCharacter::GetTotalMaxEndurance() 
{
	return BaseEndurance - CurrentEnduranceWounds;
}

float ACatSandboxCharacter::GetMaxQuickness()
{
	return BaseQuickness;
}

float ACatSandboxCharacter::GetTotalMaxQuickness() 
{
	return GetMaxQuickness() - CurrentQuicknessWounds;
}

float ACatSandboxCharacter::GetCurrentAttribute(EAttributeType Attribute)
{
  switch(Attribute) {
    case EAttributeType::AE_Health:
      return GetCurrentHP();
    case EAttributeType::AE_Toughness:
      return GetCurrentToughness();
    case EAttributeType::AE_Constitution:
      return GetCurrentConstitution();
    case EAttributeType::AE_Stamina:
      return GetCurrentStamina();
    case EAttributeType::AE_Endurance:
      return GetCurrentEndurance();
    case EAttributeType::AE_Quickness:
      return GetCurrentQuickness();
    case EAttributeType::AE_Focus:
      return GetCurrentFocus();
    case EAttributeType::AE_Clarity:
      return GetCurrentClarity();
    case EAttributeType::AE_Willpower:
      return GetCurrentWillpower();
    default:
      return 0.f;
  }
}

//Focus

float ACatSandboxCharacter::GetMaxClarity()
{
	return BaseClarity;
}

float ACatSandboxCharacter::GetTotalMaxClarity()
{
	return BaseClarity - CurrentClarityWounds;
}

float ACatSandboxCharacter::GetMaxWillpower()
{
	return BaseWillpower;
}

float ACatSandboxCharacter::GetTotalMaxWillpower() {
	return BaseWillpower - CurrentWillpowerWounds;
}

//Combat

AActor * ACatSandboxCharacter::GetCurrentTarget_Implementation()
{
	auto controller = Cast<ACatSandboxPlayerController>(GetController());
	if (controller)
	{
		return controller->GetCurrentTarget();
	}
	return nullptr;
}

bool ACatSandboxCharacter::GetIsAttackable_Implementation(UObject * ByWhom)
{
	return true;
}

float ACatSandboxCharacter::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	AController * EventInstigator,
	AActor * DamageCauser
)
{
	CurrentHealth -= DamageAmount;
	return DamageAmount;
}

bool ACatSandboxCharacter::ActivateAbility_Implementation(FName AbilityName, AActor* Target)
{
	RPCActivateAbility(AbilityName, Target);
	return true; //Normally would return a value indicating if the ability activated or not, but because of RPC we will instead need to RPC back some sort of failure state if it fails.
}

void ACatSandboxCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACatSandboxCharacter, BaseHealth);
	DOREPLIFETIME(ACatSandboxCharacter, BaseFocus);
	DOREPLIFETIME(ACatSandboxCharacter, BaseStamina);
	DOREPLIFETIME(ACatSandboxCharacter, CurrentHealth);
	DOREPLIFETIME(ACatSandboxCharacter, CurrentFocus);
	DOREPLIFETIME(ACatSandboxCharacter, CurrentStamina);
	DOREPLIFETIME(ACatSandboxCharacter, SpeciesId);
}

