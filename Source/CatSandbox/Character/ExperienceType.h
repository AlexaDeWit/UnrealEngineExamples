#pragma once

#include "Engine/UserDefinedEnum.h"
#include "ExperienceType.generated.h"

UENUM(BlueprintType)
enum class EExperienceType : uint8
{
	//Generic
	ET_BasicCrafting					UMETA(DisplayName = "Basic Crafting Experience"),
	ET_Combat							UMETA(DisplayName = "General Combat Experience"),
	//Skrimishing
	ET_Pistol							UMETA(DisplayName = "Pistol Experience"),
	ET_Rifle							UMETA(DisplayName = "Rifle Experience"),
	ET_AssaultRifle						UMETA(DisplayName = "Assault Rifle Experience"),
	//Fighting
	ET_Unarmed							UMETA(DisplayName = "Unarmed Melee Experience"),
	ET_Staff							UMETA(DisplayName = "Staff Experience"),
	ET_Sharp							UMETA(DisplayName = "Sharp Weapon Experience"),
	//Outlaw
	ET_UtilityGrenades					UMETA(DisplayName = "Utility Grenades"),
	ET_StimsCrafting					UMETA(DisplayName = "Stims Cooking Experience"),
	//Others
	ET_Construction						UMETA(DisplayName = "Construction Experience"),
	ET_Cooking							UMETA(DisplayName = "Cooking Experience"),
	ET_Cultivation						UMETA(DisplayName = "Cultivation Experience"),
	ET_RoboticsCrafting					UMETA(DisplayName = "Robotics Crafting Experience"),
	ET_Tailoring						UMETA(DisplayName = "Tailoring Experience"),
	ET_Weaponsmithing					UMETA(DisplayName = "Weaponsmithing Experience"),
	ET_OutfitterCrafting				UMETA(DisplayName = "Outfitter Crafting Experience")
};	