// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC/SupportsCombat.h"
#include "AbstractCreature.generated.h"


UCLASS(abstract)
class CATSANDBOX_API AAbstractCreature : public ACharacter, public ISupportsCombat
{
	GENERATED_BODY()

public:

	AAbstractCreature();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Interactable")
	FName DisplayName = FName("Unknown");
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	FName GetDisplayName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	UDataTable* AbilityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	UDataTable* AbilityListData;

	bool IsInCombat = false;

	virtual FName GetDisplayName_Implementation() override;
	virtual float GetMaxHP_Implementation() override;
	virtual float GetCurrentHP_Implementation() override;
	virtual float GetMaxStamina_Implementation() override;
	virtual float GetCurrentStamina_Implementation() override;
	virtual float GetCurrentFocus_Implementation() override;
	virtual float GetMaxFocus_Implementation() override;
	virtual bool GetIsAttackable_Implementation(UObject* ByWhom) override;
	virtual AActor* GetCurrentTarget_Implementation() override;
	virtual bool ActivateAbility_Implementation(FName AbilityName, AActor* Target) override;
	virtual bool GetIsInCombat_Implementation() override;
	virtual bool EnterCombatWith_Implementation(AActor* Other) override;
	virtual bool ExitCombat_Implementation() override;
	virtual bool ExitCombatWith_Implementation(AActor* Other) override;
	virtual bool IsInCombatWith_Implementation(AActor* Other) override;

	bool ChangeMovementMode(EMovementMode NewMode);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

};
