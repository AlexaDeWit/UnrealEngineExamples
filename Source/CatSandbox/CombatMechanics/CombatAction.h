#pragma once

#include "Object.h"
#include "AbilityTargetValidity.h"
#include "GameFramework/Controller.h"
#include "Character/Attributes.h"
#include "CombatAction.generated.h"


class ISupportsCombat;

UCLASS(BlueprintType, Blueprintable)
class CATSANDBOX_API UCombatAction : public UObject
{
	GENERATED_BODY()

		
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	FString GetCombatLogMessage();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ActivateAbility();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	EAbilityTargetValidity GetValidTargetType();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetInstigationData(AActor* Causer, AController* InstigatingController);

	void SetMaxRange(float MaxRange);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	float BaseAbilityDelaySeconds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	float AbilityCooldown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	float AbilityCost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	EAttributeType CostType;

	UPROPERTY(BlueprintReadOnly, Category = "Instigation")
	AActor* CastingCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Targetting")
	AActor* Target;

	UPROPERTY(BlueprintReadOnly, Category = "Instigation")
	AController* Instigator;

	UPROPERTY(BlueprintReadOnly, Category = "Instigation")
	AActor* DamageCauser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targetting")
	EAbilityTargetValidity ValidTargetType = EAbilityTargetValidity::ATV_Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targetting")
	float MaxAbilityRange = 300;

	bool HasValidSettings();

	bool RangeCheck();

	bool CostCheck();

	void UpdateCombatStates();


	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void AbilityBehaviour();
};
