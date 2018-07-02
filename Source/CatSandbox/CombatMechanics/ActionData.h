#pragma once

#include "CombatAction.h"
#include "Engine/Texture2D.h"
#include "ActionData.generated.h"

USTRUCT(BlueprintType)
struct CATSANDBOX_API FActionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCombatAction> ActionTaken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<UTexture2D> AbilityIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRange;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	float Cost;

	FActionData()
		: Name(TEXT("Name"))
		, Description(TEXT("Description"))
		, MaxRange(300.f)
		, Cost(100.f)
	{}
};
