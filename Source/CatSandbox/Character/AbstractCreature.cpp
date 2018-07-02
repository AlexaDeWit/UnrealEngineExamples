// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "AbstractCreature.h"

// Sets default values
AAbstractCreature::AAbstractCreature()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -97.f));
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCharacterMovement()->AirControl = 0.f;

	ConstructorHelpers::FObjectFinder<UDataTable> AbilitiesDataTable(TEXT("DataTable'/Game/Abilities/Actions.Actions'"));
	if (AbilitiesDataTable.Succeeded())
	{
		AbilityData = AbilitiesDataTable.Object;
	}
	ConstructorHelpers::FObjectFinder<UDataTable> AbilityListDataTable(TEXT("DataTable'/Game/Abilities/AbilityLists.AbilityLists'"));
	if (AbilityListDataTable.Succeeded())
	{
		AbilityListData = AbilityListDataTable.Object;
	}
}

float AAbstractCreature::GetCurrentHP_Implementation()
{
	return 250;
}

float AAbstractCreature::GetMaxStamina_Implementation()
{
	return 250;
}

float AAbstractCreature::GetCurrentStamina_Implementation()
{
	return 250;
}

float AAbstractCreature::GetCurrentFocus_Implementation()
{
	return 250;
}

float AAbstractCreature::GetMaxFocus_Implementation()
{
	return 250;
}

float AAbstractCreature::GetMaxHP_Implementation()
{
	return 250;
}

bool AAbstractCreature::GetIsAttackable_Implementation(UObject * ByWhom)
{
	return false;
}

AActor * AAbstractCreature::GetCurrentTarget_Implementation()
{
	return nullptr;
}

bool AAbstractCreature::ActivateAbility_Implementation(FName AbilityName, AActor* Target)
{
	return true;
}

bool AAbstractCreature::GetIsInCombat_Implementation()
{
	return IsInCombat;
}

bool AAbstractCreature::EnterCombatWith_Implementation(AActor * Other)
{
	return true; //Doesn't do shit in abstract creature lol
}

bool AAbstractCreature::ExitCombat_Implementation()
{
	return true;
}

bool AAbstractCreature::ExitCombatWith_Implementation(AActor* Other)
{
	return true;
}

bool AAbstractCreature::IsInCombatWith_Implementation(AActor* Other)
{
	return false;
}

// Called when the game starts or when spawned
void AAbstractCreature::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbstractCreature::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAbstractCreature::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);
}

FName AAbstractCreature::GetDisplayName_Implementation()
{
	return DisplayName;
}


void AAbstractCreature::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAbstractCreature, DisplayName);
}

bool AAbstractCreature::ChangeMovementMode(EMovementMode NewMode) {
	//Must be cast because this function originally comes from pawns, and returns a UPawnMovementComponent, which is a supertype of UCharacterMovementComponent
	//CharacterMovementComponents are an expanded type of Pawn Movement Component.
	auto movementComp = Cast<UCharacterMovementComponent>(GetMovementComponent()); //Since we are calling this function from a Character, the movementcomponent type is a charactermovementcompoent
	//TODO: change this to be governed by the internal state machine
	if (movementComp) //Movement modes are only valid for character movement component types.
	{
		movementComp->SetMovementMode(NewMode);
		return true;
	}
	return false;
}