// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Character/Attributes.h"
#include "Character/AbstractCreature.h"
#include "AI/Navigation/NavigationInvokerComponent.h"
#include "CatSandboxCharacter.generated.h"

//Attribute defines
//Regen should be 1/100 of the third stat (Constitution, Endurance, Willpower)

//Health
#define PLAYER_BASE_HEALTH 500
#define PLAYER_BASE_TOUGHNESS 250
#define PLAYER_BASE_CONSTITUTION 250
//Stamina
#define PLAYER_BASE_STAMINA 250
#define PLAYER_BASE_QUICKNESS 250
#define PLAYER_BASE_ENDURANCE 250
//Focus
#define PLAYER_BASE_FOCUS 250
#define PLAYER_BASE_CLARITY 250
#define PLAYER_BASE_WILLPOWER 250

UCLASS(config=Game)
class ACatSandboxCharacter : public AAbstractCreature
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Navigation", meta = (AllowPrivateAccess = "true"))
	class UNavigationInvokerComponent* NavInvoker;

public:
	ACatSandboxCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	void PrintMessageToScreen(FString Text);

	virtual void UnPossessed() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	bool GetIsInitialised();

protected:


	//Stats

	//health
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseHealth = PLAYER_BASE_HEALTH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentHealth = PLAYER_BASE_HEALTH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentHealthWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxHealth = PLAYER_BASE_HEALTH;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseToughness = PLAYER_BASE_TOUGHNESS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentToughness = PLAYER_BASE_TOUGHNESS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentToughnessWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxToughness = PLAYER_BASE_TOUGHNESS;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseConstitution = PLAYER_BASE_CONSTITUTION;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentConstitution = PLAYER_BASE_CONSTITUTION;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentConstitutionWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxConstitution = PLAYER_BASE_CONSTITUTION;



	//Stamina
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseStamina = PLAYER_BASE_STAMINA;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentStamina = PLAYER_BASE_STAMINA;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentStaminaWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxStamina = PLAYER_BASE_CLARITY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseQuickness = PLAYER_BASE_QUICKNESS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentQuickness = PLAYER_BASE_QUICKNESS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentQuicknessWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxQuickness = PLAYER_BASE_CLARITY;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseEndurance = PLAYER_BASE_ENDURANCE;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentEndurance = PLAYER_BASE_ENDURANCE;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentEnduranceWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxEndurance = PLAYER_BASE_CLARITY;

	//Focus
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseFocus = PLAYER_BASE_FOCUS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentFocus = PLAYER_BASE_FOCUS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentFocusWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxFocus = PLAYER_BASE_CLARITY;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseClarity = PLAYER_BASE_CLARITY;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentClarity = PLAYER_BASE_CLARITY;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentClarityWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxClarity = PLAYER_BASE_CLARITY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float BaseWillpower = PLAYER_BASE_WILLPOWER;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentWillpower = PLAYER_BASE_WILLPOWER;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float CurrentWillpowerWounds = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Attributes")
	float TotalMaxWillpower = PLAYER_BASE_WILLPOWER;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Customisation")
	FName SpeciesId;

	bool IsInitialised = false;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void RPCActivateAbility(FName AbilityName, AActor* Target);

	//Player specific logic for stat management.
	virtual float GetCurrentHP_Implementation() override;
	virtual float GetCurrentStamina_Implementation() override;
	virtual float GetCurrentFocus_Implementation() override;

	float GetCurrentToughness();
	float GetCurrentConstitution();
	float GetCurrentEndurance();
	float GetCurrentQuickness();
	float GetCurrentClarity();
	float GetCurrentWillpower();
	//Wounds
	float GetCurrentHealthWounds();
	float GetCurrentToughnessWounds();
	float GetCurrentConstitutionWounds();
	float GetCurrentStaminaWounds();
	float GetCurrentEnduranceWounds();
	float GetCurrentQuicknessWounds();
	float GetCurrentFocusWounds();
	float GetCurrentClarityWounds();
	float GetCurrentWillpowerWounds();

	float GetTotalMaxConstitution();
	float GetTotalMaxToughness();

	float GetTotalMaxQuickness();
	float GetTotalMaxEndurance();

	float GetTotalMaxClarity();
	float GetTotalMaxWillpower();


	virtual float GetMaxHP_Implementation() override;
	virtual float GetMaxStamina_Implementation() override;
	virtual float GetMaxFocus_Implementation() override;

	float GetMaxToughness();
	float GetMaxConstitution();
	float GetMaxEndurance();
	float GetMaxQuickness();
	float GetMaxClarity();
	float GetMaxWillpower();
  
  UFUNCTION(BlueprintCallable, Category = "Attributes")
  float GetCurrentAttribute(EAttributeType Attribute);

	virtual AActor* GetCurrentTarget_Implementation() override;
	virtual bool GetIsAttackable_Implementation(UObject* ByWhom) override;


	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser
	) override;

	virtual bool ActivateAbility_Implementation(FName AbilityName, AActor* Target) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};

