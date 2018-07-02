#pragma once

#include "Engine/UserDefinedEnum.h"
#include "CombatSkillMod.generated.h"

UENUM(BlueprintType)
enum class ECombatSkillMod : uint8
{
	//Generic
	CSM_EmptyWorkaround			UMETA(DisplayName = "Empty, Workaround"),
	//Dodge
	CSM_Dodge					UMETA(DisplayName = "Dodge"),
	CSM_PistolDodge				UMETA(DisplayName = "Dodge using Pistol"),
	CSM_RifleDodge				UMETA(DisplayName = "Dodge using Rifle"),
	CSM_AssaultRifleDodge		UMETA(DisplayName = "Dodge using Assault Rifle"),
	CSM_UnarmedDodge			UMETA(DisplayName = "Dodge while Unarmed"),
	CSM_OneHanddodge			UMETA(DisplayName = "Dodge using One-handed"),
	CSM_TwoHandDodge			UMETA(DisplayName = "Dodge using two-handed"),
	CSM_ExoticDodge				UMETA(DisplayName = "Dodge using exotic"),
	CSM_StaffDodge				UMETA(DisplayName = "Dodge using Staves"),
	CSM_CrouchDodge				UMETA(DisplayName = "Dodge while Crouching"),
	CSM_ProneDodge				UMETA(DisplayName = "Dodge while Prone"),
	//Accuracy
	CSM_Accuracy				UMETA(DisplayName = "Accuracy"),
	CSM_PistolAccuracy			UMETA(DisplayName = "Accuracy using Pistol"),
	CSM_RifleAccuracy			UMETA(DisplayName = "Accuracy using Rifle"),
	CSM_AssaultRifleAccuracy	UMETA(DisplayName = "Accuracy using Assault Rifle"),
	CSM_UnarmedAccuracy			UMETA(DisplayName = "Accuracy while Unarmed"),
	CSM_OneHandAccuracy			UMETA(DisplayName = "Accuracy using One-handed"),
	CSM_TwoHandAccuracy			UMETA(DisplayName = "Accuracy using Two-handed"),
	CSM_ExoticAccuracy			UMETA(DisplayName = "Accuracy using Exotic"),
	CSM_StavesAccuracy			UMETA(DisplayName = "Accuracy using Staves"),
	//Attack Speed
	CSM_AttackSpeed				UMETA(DisplayName = "Attack Speed"),
	CSM_PistolAttackSpeed		UMETA(DisplayName = "Attack Speed using Pistol"),
	CSM_RifleAttackSpeed		UMETA(DisplayName = "Attack Speed using Rifle"),
	CSM_AssaultRifleAttackSpeed	UMETA(DisplayName = "Attack Speed using Assault Rifle"),
	CSM_UnarmedAttackSpeed		UMETA(DisplayName = "Attack Speed while Unarmed"),
	CSM_OneHandAttackSpeed		UMETA(DisplayName = "Attack Speed using One-handed"),
	CSM_TwoHandAttackSpeed		UMETA(DisplayName = "Attack Speed using Two-handed"),
	CSM_ExoticAttackSpeed		UMETA(DisplayName = "Attack Speed using Exotic"),
	CSM_StavesAttackSpeed		UMETA(DisplayName = "Attack Speed using Staves"),
	//Others
	CSM_UnarmedDamage			UMETA(Displayname = "Damage while Unarmed")


};