#pragma once

#include "Engine/UserDefinedEnum.h"
#include "CreatureType.generated.h"

UENUM(BlueprintType)
enum class ECreatureType : uint8
{
	ECT_Humanoid				UMETA(DisplayName = "Humanoid"),
	ECT_Carnivorous				UMETA(DisplayName = "Carnivorous"),
	ECT_Robotic					UMETA(DisplayName = "Robotic"),
	ECT_Insectoid				UMETA(DisplayName = "Insectoid"),
	ECT_Avian					UMETA(DisplayName = "Avian"),
	ECT_Herbivore				UMETA(DisplayName = "Herbivore"),
	ECT_Reptilian				UMETA(DisplayName = "Reptilian")
};
