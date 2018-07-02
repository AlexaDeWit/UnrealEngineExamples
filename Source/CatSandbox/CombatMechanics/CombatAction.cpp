#include "CatSandbox.h"
#include "Character/CatSandboxCharacter.h"
#include "NPC/SupportsCombat.h"
#include "CombatAction.h"

void UCombatAction::SetTarget(AActor * NewTarget)
{
	Target = Cast<ISupportsCombat>(NewTarget) ? NewTarget : nullptr;
}

void UCombatAction::SetInstigationData(AActor * Causer, AController * InstigatingController)
{
	Instigator = InstigatingController;
	DamageCauser = Causer;
}

void UCombatAction::SetMaxRange(float MaxRange)
{
	MaxAbilityRange = MaxRange;
}

bool UCombatAction::HasValidSettings()
{
	auto owning_pawn = Cast<ISupportsCombat>(DamageCauser);
	if (!owning_pawn || !Target)
	{
		return false;
	}
	switch (ValidTargetType)
	{
		case EAbilityTargetValidity::ATV_Enemy:
			if (ISupportsCombat::Execute_GetIsAttackable(Target, DamageCauser))
			{
				return true;
			}
			break;
		case EAbilityTargetValidity::ATV_Friend:
			if (!ISupportsCombat::Execute_GetIsAttackable(Target, DamageCauser))
			{
				return true;
			}
			break;
		case EAbilityTargetValidity::ATV_Self:
			Target = Cast<APawn>(DamageCauser);
			if (Target)
			{
				return true;
			}
			break;
	}
	return false;
}

bool UCombatAction::RangeCheck()
{
	if (!Target || !DamageCauser)
	{
		return false;
	}
	auto dist = DamageCauser->GetDistanceTo(Target);
	if(dist < MaxAbilityRange)
	{
		return true;
	}
	return false;
}

//Review me
bool UCombatAction::CostCheck()
{
	if (!Target || !DamageCauser)
	{
		return false;
	}

	auto CastingPlayerCharacter = Cast<ACatSandboxCharacter>(DamageCauser);
	
	if (CastingPlayerCharacter)
	{
    if(CastingPlayerCharacter->GetCurrentAttribute(CostType) > AbilityCost) return true;
    return false;
	}
  return true; //Don't worry about costs on non-players
}

void UCombatAction::UpdateCombatStates()
{
	switch (ValidTargetType)
	{
	case EAbilityTargetValidity::ATV_Enemy:
		ISupportsCombat::Execute_EnterCombatWith(DamageCauser, Target);
		ISupportsCombat::Execute_EnterCombatWith(Target, DamageCauser);
		break;
	case EAbilityTargetValidity::ATV_Friend:
		//Assist-Combat-Entering-Logic goes here
		break;
	case EAbilityTargetValidity::ATV_Self:
		break;
	}
}

void UCombatAction::ActivateAbility()
{
	if (HasValidSettings() && RangeCheck() && CostCheck())
	{
		this->AbilityBehaviour();
		UpdateCombatStates();
		UE_LOG(LogTemp, Warning, TEXT("Ability Activated!"));
	}
}

EAbilityTargetValidity UCombatAction::GetValidTargetType()
{
	return ValidTargetType;
}
