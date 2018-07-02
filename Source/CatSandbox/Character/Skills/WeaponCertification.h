#pragma once

#include "Engine/UserDefinedEnum.h"
#include "WeaponCertification.generated.h"

UENUM(BlueprintType)
enum class EWeaponCertification : uint8
{
	WC_EmptyWorkaround					UMETA(DisplayName = "Empty, Workaround"),
	//Meta Tier 1
	WC_K9Pistol							UMETA(DisplayName = "K-35 Issue Pistol"),
	WC_ScoutRifle						UMETA(DisplayName = "Reconnaissance Scout Rifle"),
	WC_EnoumRattlingAssaultRifle		UMETA(DisplayName = "Enoum Rattling Assault Rifle"),
	WC_Switchblade						UMETA(DisplayName = "Switchblade"),
	WC_Staff							UMETA(DisplayName = "Staff"),
	//Meta/Tier 2
	WC_MetalStaff						UMETA(DisplayName = "Metal Staff"),
	WC_Cleaver							UMETA(DisplayName = "Cleaver"),
	WC_CombatKnife						UMETA(DisplayName = "Combat Knife"),
	WC_AmnHuntingRifle					UMETA(DisplayName = "Amn Hunting Rifle"),
	WC_R56AassaultRifle					UMETA(DisplayName = "R-56 Assault Rifle"),
	WC_X12BlasterPistol					UMETA(DisplayName = "X-12 Blaster Pistol"),
	//Meta/Tier 3
	WC_Sword							UMETA(DisplayName = "Sword"),
	WC_ButterflyKnife					UMETA(DisplayName = "Butterfly Knife"),
	WC_GracefulStaff					UMETA(DisplayName = "Graceful Staff"),
	WC_GunkanPlasmaRifle				UMETA(DisplayName = "Gunkan Plasma Rifle"),
	WC_ArsanBlastingAssaultRifle		UMETA(DisplayName = "Arsan Blasting Assault Rifle"),
	WC_UntaScoutPistol					UMETA(DisplayName = "Unta Scout Pistol"),
	//Meta/Tier 4
	WC_WristBlade						UMETA(DisplayName = "Wrist-Blade")
};