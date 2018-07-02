#pragma once


#include "Character/AbstractCreature.h"
#include "CombatMechanics/ThreatTableEntry.h"
#include "BasicNPC.generated.h"

struct FNPCData;

UCLASS(BlueprintType, Blueprintable)
class ABasicNPC : public AAbstractCreature
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNPCDeathDelegate);

public:

	ABasicNPC();
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FNPCDeathDelegate DeathDelegate;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController * EventInstigator,
		AActor * DamageCauser
	) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void Setup(FNPCData* NPCData);

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	TArray<FName> AbilityIds = TArray<FName>();

	virtual float GetMaxHP_Implementation() override;
	virtual float GetCurrentHP_Implementation() override;
	virtual float GetMaxStamina_Implementation() override;
	virtual float GetCurrentStamina_Implementation() override;
	virtual float GetCurrentFocus_Implementation() override;
	virtual float GetMaxFocus_Implementation() override;
	virtual bool EnterCombatWith_Implementation(AActor* Other) override;
	virtual bool ExitCombat_Implementation() override;
	virtual bool ExitCombatWith_Implementation(AActor* Other) override;
	virtual bool GetIsInCombat_Implementation() override;
	virtual bool GetIsAttackable_Implementation(UObject* ByWhom) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void Destroyed() override;

protected:
	void InitialiseStats(FNPCData* NPCData);

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Behaviour")
	bool DoesWander;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Behaviour")
	int MaxWanderRange;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	float CurrentHealth;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	float MaxFocus;
	
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	float CurrentFocus;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	float MaxStamina;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	float CurrentStamina;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Initialisation")
	bool InitialisedForCombat = false;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Combat")
	TArray<FThreatTableEntry> ThreatTable = TArray<FThreatTableEntry>();

	int FindThreatTableIndexFor(AActor* Opponent);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void NPCDie();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Personality")
	FName PersonalityRowId;

	UPROPERTY(BlueprintReadOnly, Category = "Personality")
	UDataTable* PersonalityData;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AddThreatFor(AActor* Opponent, float ThreatAmount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int FindOrCreateThreatIndexFor(AActor* Opponent);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=NPCMeshChanged, Category = "Visuals")
	USkeletalMesh* NPCMesh;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=NPCAnimationChanged, Category = "Visuals")
	UAnimBlueprintGeneratedClass* NPCAnimationClass;

	UFUNCTION(BlueprintCallable, Category="Visuals")
	void NPCMeshChanged();

	UFUNCTION(BlueprintCallable, Category = "Visuals")
	void NPCAnimationChanged();

};
