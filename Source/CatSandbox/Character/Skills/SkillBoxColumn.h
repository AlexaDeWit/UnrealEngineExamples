#pragma once

#include "SkillBoxColumn.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FSkillBoxColumn : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName SkillBoxTier1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName SkillBoxTier2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName SkillBoxTier3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName SkillBoxTier4;

	FSkillBoxColumn()
		: SkillBoxTier1(FName())
		, SkillBoxTier2(FName())
		, SkillBoxTier3(FName())
		, SkillBoxTier4(FName())
	{}
};
