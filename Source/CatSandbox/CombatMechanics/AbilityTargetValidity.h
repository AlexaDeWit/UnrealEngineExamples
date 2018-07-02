#pragma once

#include "Engine/UserDefinedEnum.h"
#include "AbilityTargetValidity.generated.h"

UENUM(BlueprintType)
enum class EAbilityTargetValidity: uint8
{
	ATV_Self		UMETA(DisplayName = "Can target self"),
	ATV_Friend		UMETA(DisplayName = "Can target friendly"),
	ATV_Enemy		UMETA(DisplayName = "Can target hostile")
};
