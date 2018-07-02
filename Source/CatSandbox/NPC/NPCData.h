#pragma once

#include "CreatureType.h"
#include "NPCData.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FNPCData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<USkeletalMesh> NPCMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<UAnimBlueprint> NPCAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityListId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PersonalityId;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoesWander;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWanderRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECreatureType CreatureType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFocus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFocus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAggressive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LootTableId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LootChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HarvestBones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HarvestMeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HarvestHide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GroupSize;

	FNPCData()
		: Name(FName("Name"))
		, DoesWander(true)
		, MaxWanderRange(1000.f)
		, CreatureType(ECreatureType::ECT_Humanoid)
		, MinHealth(200.f)
		, MaxHealth(250.f)
		, MinStamina(100.f)
		, MaxStamina(125.f)
		, MinFocus(100.f)
		, MaxFocus(125.f)
		, MinDamage(10.f)
		, MaxDamage(20.f)
		, AttackSpeed(2.f)
		, MovementSpeed(600.f)
		, IsAggressive(false)
		, LootTableId(FName("None"))
		, LootChance(0.f)
		, HarvestBones(0)
		, HarvestMeat(0)
		, HarvestHide(0)
		, GroupSize(1)
		{}
};
