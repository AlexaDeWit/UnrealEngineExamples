#include "CatSandbox.h"
#include "CombatMechanics/AbilityList.h"
#include "NPCData.h"
#include "NPC/AI/NPCAIController.h"
#include "BasicNPC.h"

ABasicNPC::ABasicNPC() : Super()
{
	AIControllerClass = ANPCAIController::StaticClass();
	ConstructorHelpers::FObjectFinder<UDataTable> PersonalitiesDataTable(TEXT("DataTable'/Game/NPCs/NPCPersonalities.NPCPersonalities'"));
	if (PersonalitiesDataTable.Succeeded())
	{
		PersonalityData = PersonalitiesDataTable.Object;
	}
	bNetLoadOnClient = false;
	bAlwaysRelevant = true;
	GetMesh()->SetIsReplicated(true);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (MeshFinder.Succeeded())
	{
		//Default mesh testing
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
	}	
}
float ABasicNPC::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	AController * EventInstigator,
	AActor * DamageCauser
)
{
	CurrentHealth -= DamageAmount;
	AddThreatFor(DamageCauser, DamageAmount);
	return DamageAmount;
}

void ABasicNPC::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetEnableGravity(true);
	UE_LOG(LogTemp, Warning, TEXT("I'm alive!"));
}

// Called every frame
void ABasicNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(InitialisedForCombat && CurrentHealth <= 0 && Role == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("I died!"));
		NPCDie();
	}
}


void ABasicNPC::Setup(FNPCData* NPCData)
{
	DisplayName = NPCData->Name;
	DoesWander = NPCData->DoesWander;
	MaxWanderRange = NPCData->MaxWanderRange;
	InitialiseStats(NPCData);
	if(NPCData->NPCMesh.IsValid() && NPCData->NPCAnimation.IsValid())
	{
		NPCMesh = NPCData->NPCMesh.Get();
		GetMesh()->SetSkeletalMesh(NPCMesh);
		GetMesh()->SetEnableGravity(true);
		NPCAnimationClass = NPCData->NPCAnimation.Get()->GetAnimBlueprintGeneratedClass();
		GetMesh()->SetAnimInstanceClass(NPCAnimationClass);
		auto row = AbilityListData->FindRow<FAbilityList>(NPCData->AbilityListId, "Getting ability list for NPC");
		PersonalityRowId = NPCData->PersonalityId;
		if (row)
		{
			AbilityIds = row->AbilityIds;
		}
	}
}
void ABasicNPC::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasicNPC, MaxHealth);
	DOREPLIFETIME(ABasicNPC, MaxFocus);
	DOREPLIFETIME(ABasicNPC, MaxStamina);
	DOREPLIFETIME(ABasicNPC, CurrentHealth);
	DOREPLIFETIME(ABasicNPC, CurrentFocus);
	DOREPLIFETIME(ABasicNPC, CurrentStamina);
	DOREPLIFETIME(ABasicNPC, InitialisedForCombat);
	DOREPLIFETIME(ABasicNPC, NPCMesh);
	DOREPLIFETIME(ABasicNPC, NPCAnimationClass);
	DOREPLIFETIME(ABasicNPC, ThreatTable);
}

void ABasicNPC::Destroyed()
{
	Super::Destroyed();
}

void ABasicNPC::InitialiseStats(FNPCData* NPCData)
{
	MaxHealth = NPCData->MaxHealth;
	MaxFocus = NPCData->MaxFocus;
	MaxStamina = NPCData->MaxStamina;
	CurrentHealth = MaxHealth;
	CurrentFocus = MaxFocus;
	CurrentStamina = MaxStamina;
	InitialisedForCombat = true;
	bCanBeDamaged = true;
}
float ABasicNPC::GetCurrentHP_Implementation()
{
	return CurrentHealth;
}

float ABasicNPC::GetMaxStamina_Implementation()
{
	return MaxStamina;
}

float ABasicNPC::GetCurrentStamina_Implementation()
{
	return CurrentStamina;
}

float ABasicNPC::GetCurrentFocus_Implementation()
{
	return CurrentFocus;
}

float ABasicNPC::GetMaxFocus_Implementation()
{
	return MaxFocus;
}
bool ABasicNPC::EnterCombatWith_Implementation(AActor * Other)
{
	if (!Cast<ISupportsCombat>(Other)) { return false; }
	FindOrCreateThreatIndexFor(Other);
	return true;
}

bool ABasicNPC::ExitCombat_Implementation()
{
	while (ThreatTable.Num() > 0)
	{
		auto e = ThreatTable.Pop();
		ISupportsCombat::Execute_ExitCombatWith(e.CombatTarget, this);
	}
	return true;
}

bool ABasicNPC::ExitCombatWith_Implementation(AActor* Other)
{
	auto i = FindThreatTableIndexFor(Other);
	if (i != -1)
	{
		ThreatTable.RemoveAt(i);
		if (ISupportsCombat::Execute_IsInCombatWith(Other, this))
		{
			ISupportsCombat::Execute_ExitCombatWith(Other, this);
		}
		return true;
	}
	return false;
}

bool ABasicNPC::GetIsInCombat_Implementation()
{
	return ThreatTable.Num() > 0;
}

float ABasicNPC::GetMaxHP_Implementation()
{
	return MaxHealth;
}

int ABasicNPC::FindThreatTableIndexFor(AActor * Opponent)
{
	if (!Cast<ISupportsCombat>(Opponent)) { return -1; }
	for(int i = 0; i < ThreatTable.Num(); i++)
	{
		auto e = ThreatTable[i];
		if (e.CombatTarget == Opponent)
		{
			return i;
		}
	}
	return -1;
}

void ABasicNPC::NPCDie()
{
	if (DeathDelegate.IsBound())
	{
		DeathDelegate.Broadcast();
	}
	Destroy(false, false);
}

void ABasicNPC::AddThreatFor(AActor * Opponent, float ThreatAmount)
{
	auto index = FindOrCreateThreatIndexFor(Opponent);
	if (index != -1)
	{
		auto entry = ThreatTable[index];
		entry.ThreatLevel += ThreatAmount;
		ThreatTable[index] = entry;
	}
}

int ABasicNPC::FindOrCreateThreatIndexFor(AActor * Opponent)
{
	if (!Cast<ISupportsCombat>(Opponent)) { return -1; }
	auto index = FindThreatTableIndexFor(Opponent);
	if (index == -1)
	{
		return ThreatTable.Add(FThreatTableEntry(Opponent));
	}
	return index;
}

void ABasicNPC::NPCMeshChanged()
{
	GetMesh()->SetSkeletalMesh(NPCMesh);
}

void ABasicNPC::NPCAnimationChanged()
{
	GetMesh()->SetAnimInstanceClass(NPCAnimationClass);
}

bool ABasicNPC::GetIsAttackable_Implementation(UObject * ByWhom)
{
	//Temporary but checking this is important!
	return InitialisedForCombat;
}
