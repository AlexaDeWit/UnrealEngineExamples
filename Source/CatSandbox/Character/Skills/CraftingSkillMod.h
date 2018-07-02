#pragma once

#include "Engine/UserDefinedEnum.h"
#include "CraftingSkillMod.generated.h"

UENUM(BlueprintType)
enum class ECraftingSkillMod : uint8
{
	CRSM_EmptyWorkaround				UMETA(DisplayName = "Empty, Workaround"),
	CRSM_EngineeringAssembly			UMETA(DisplayName = "Engineering Assembly"),
	CRSM_EngineeringExperimenting		UMETA(DisplayName = "Engineering Experimenting"),
	CRSM_ElectronicsAssembly			UMETA(DisplayName = "Electronics Assembly"),
	CRSM_ElectronicsExperimenting		UMETA(DisplayName = "Electronics Experimenting"),
	CRSM_MeleeWeaponAssembly			UMETA(DisplayName = "Melee Weapon Assembly"),
	CRSM_MeleeWeaponExperimenting		UMETA(DisplayName = "Melee Weapon Experimenting"),
	CRSM_StructureAssembly				UMETA(DisplayName = "Structure Assembly"),
	CRSM_StructureExperimenting			UMETA(DisplayName = "Structure Experimenting"),
	CRSM_SmallArmsAssembly				UMETA(DisplayName = "Small-Arms Assembly"),
	CRSM_SmallArmsExperimenting			UMETA(DisplayName = "Small-Arms Experimenting"),
	CRSM_ArmourAssembly					UMETA(DisplayName = "Outfitting Assembly"),
	CRSM_ArmourExperimenting			UMETA(DisplayName = "Outfitting Experimenting"),
	CRSM_AssemblySpeed					UMETA(DisplayName = "Assembly Speed"),
	CRSM_SurvivalCrafting				UMETA(DisplayName = "Survival crafting"),
	CRSM_HousecraftAssembly				UMETA(DisplayName = "Housecraft Assembly"),
	CRSM_HousecraftExperimenting		UMETA(DisplayName = "Housecraft Experimenting"),
	CRSM_Cooking						UMETA(DisplayName = "Cooking"),
	CRSM_CookingExperimenting			UMETA(DisplayName = "Cooking Experimenting"),
	CRSM_Brewing						UMETA(DisplayName = "Brewing"),
	CRSM_BrewingExperimenting			UMETA(DisplayName = "Brewing Experimenting"),
	CRSM_UtilityGrenades				UMETA(Displayname = "Utility Grenade Crafting"),
	CRSM_UtilityGrenadesExperimenting	UMETA(Displayname = "Utility Grenade Experiementing"),
	CRSM_StimsCooking					UMETA(Displayname = "Stims cooking"),
	CRSM_StimsCookingExperimenting		UMETA(Displayname = "Stims cooking experimenting")
};