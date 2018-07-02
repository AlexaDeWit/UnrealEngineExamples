// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Targettable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class CATSANDBOX_API UTargettable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class CATSANDBOX_API ITargettable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	FName GetDisplayName();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	float GetMaxHP();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	float GetCurrentHP();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	float GetMaxStamina();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	float GetCurrentStamina();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	float GetCurrentFocus();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	float GetMaxFocus();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	bool GetIsAttackable(UObject* ByWhom);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targetting")
	AActor* GetCurrentTarget();

};
