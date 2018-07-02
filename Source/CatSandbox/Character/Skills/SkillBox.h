#pragma once

#include "CombatMechanics/CombatSkillMod.h"
#include "Character/Skills/CraftingSkillMod.h"
#include "Character/Skills/OtherSkillMod.h"
#include "Character/Skills/WeaponCertification.h"
#include "Character/ExperienceType.h"
#include "SkillBox.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FSkillBox : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Mods")
	TMap<ECombatSkillMod, int> CombatSkillMods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Mods")
	TMap<ECraftingSkillMod, int> CraftingSkillMods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Mods")
	TMap<EOtherSkillMod, int> OtherSkillMods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Certifications")
	TArray<EWeaponCertification> WeaponCertifications;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<FName> AwardedAbilityIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Schematics")
	TArray<FName> AwardedSchematics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	int ExperienceCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	EExperienceType RequiredExperienceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	int SkillPointCost;


	FSkillBox()
		: Name(TEXT("Name"))
		, Description(TEXT("Description"))
		, CombatSkillMods(TMap<ECombatSkillMod, int>())
		, CraftingSkillMods(TMap<ECraftingSkillMod, int>())
		, OtherSkillMods(TMap<EOtherSkillMod, int>())
		, WeaponCertifications(TArray<EWeaponCertification>())
		, AwardedAbilityIds(TArray<FName>())
		, AwardedSchematics(TArray<FName>())
		, ExperienceCost(1000)
		, RequiredExperienceType(EExperienceType::ET_Combat)
		, SkillPointCost(5)
	{}
};
