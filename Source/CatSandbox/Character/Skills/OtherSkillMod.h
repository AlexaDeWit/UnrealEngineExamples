#pragma once

#include "Engine/UserDefinedEnum.h"
#include "OtherSkillMod.generated.h"

UENUM(BlueprintType)
enum class EOtherSkillMod : uint8
{
	OSM_EmptyWorkaround     UMETA(DisplayName = "Empty, Workaround"),
	OSM_HarvestingAmount	UMETA(DisplayName = "Creature harvesting amount"),
	OSM_HarvestingSpeed		UMETA(DisplayName = "Creature harvesting speed"),
	OSM_CrouchMoveSpeed		UMETA(DisplayName = "Faster Movement While Crouching"),
	OSM_ProneMoveSpeed		UMETA(DisplayName = "Faster Movement While Prone")

};