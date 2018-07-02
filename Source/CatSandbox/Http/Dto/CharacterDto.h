#pragma once

#include "CharacterDto.generated.h"
USTRUCT(BlueprintType)
struct CATSANDBOX_API FCharacterDto {

	GENERATED_USTRUCT_BODY()

public:


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
    FString Id;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		FString Name;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		FString SpeciesName;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float LocationX;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float LocationY;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float LocationZ;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentHealth;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentToughness;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentConstitution;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentStamina;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentQuickness;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentEndurance;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentFocus;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentClarity;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
		float CurrentWillpower;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Http|Character")
    bool IsNewCharacter;


	FCharacterDto()
		: Id(TEXT("UKNOWN CHARACTER ID"))
		, Name(TEXT("Unknown"))
		, SpeciesName(TEXT("Human"))
		, LocationX(0.f)
		, LocationY(0.f)
		, LocationZ(0.f)
		, CurrentHealth(1)
		, CurrentToughness(1)
		, CurrentConstitution(1)
		, CurrentStamina(1)
		, CurrentQuickness(1)
		, CurrentEndurance(1)
		, CurrentFocus(1)
		, CurrentClarity(1)
		, CurrentWillpower(1)
    , IsNewCharacter(true)
	{
	};
};
