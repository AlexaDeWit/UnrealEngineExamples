#pragma once

#include "SkillTree.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FSkillTree : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName NoviceBoxId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName Column1Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName Column2Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName Column3Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName Column4Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName SpecialisationOptionOneId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FName SpecialisationOptionTwoId;
	
	FSkillTree()
		: Name(TEXT("Name"))
		, Description(TEXT("Description"))
	{}
};
