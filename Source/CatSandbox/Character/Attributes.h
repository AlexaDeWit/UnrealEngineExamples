#pragma once
#include "Engine/UserDefinedEnum.h"
#include "Attributes.generated.h"

UENUM(BlueprintType)

enum class EAttributeType : uint8
{
	AE_Health			UMETA(DisplayName = "Health"),
	AE_Toughness		UMETA(DisplayName = "Toughness"),
	AE_Constitution		UMETA(DisplayName = "Constitution"),

	AE_Stamina			UMETA(DisplayName = "Stamina"),
	AE_Endurance		UMETA(DisplayName = "Endurance"),
	AE_Quickness		UMETA(DisplayName = "Quickness"),

	AE_Focus			UMETA(DisplayName = "Focus"),
	AE_Clarity			UMETA(DisplayName = "Clarity"),
	AE_Willpower		UMETA(DisplayName = "Willpower")
};