#pragma once

#include "Engine/UserDefinedEnum.h"
#include "DamageTypes.generated.h"

//DEPRECATED DO NOT USE
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	DT_Kinetic		UMETA(DisplayName="Kinetic Damage"),
	DT_Blast		UMETA(DisplayName = "Blast Damage"),
	DT_Energy		UMETA(DisplayName = "Energy Damage"),
	DT_Heat			UMETA(DisplayName = "Heat Damage")
};