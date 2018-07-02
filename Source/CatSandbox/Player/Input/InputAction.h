#pragma once

#include "Engine/UserDefinedEnum.h"
#include "InputAction.generated.h"

UENUM(BlueprintType)
enum class EInputAction : uint8
{
	IA_ToggleSkillBook				    UMETA(DisplayName = "Toggle SkillBook"),
	IA_ToggleProfessionsBrowser		UMETA(DisplayName = "Toggle Professions Browser"),
  IA_ToggleEscapeMenu         UMETA(DisplayName = "Toggle Settings Menu")
};
