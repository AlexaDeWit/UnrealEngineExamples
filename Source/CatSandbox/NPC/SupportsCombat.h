#pragma once

#include "Interfaces/Targettable.h"
#include "GameFramework/Pawn.h"
#include "SupportsCombat.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class CATSANDBOX_API USupportsCombat : public UTargettable
{
	GENERATED_UINTERFACE_BODY()
};

class CATSANDBOX_API ISupportsCombat : public ITargettable
{
	GENERATED_IINTERFACE_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool ActivateAbility(FName AbilityName, AActor* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool GetIsInCombat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool EnterCombatWith(AActor* Other);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool ExitCombat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool ExitCombatWith(AActor* Other);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool IsInCombatWith(AActor* Other);
	
};