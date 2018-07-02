// Fill out your copyright notice in the Description page of Project Settings.

#include "CatSandbox.h"
#include "NPCSpawner.h"


// Sets default values
ANPCSpawner::ANPCSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SphereRoot;
	SpawnBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Bounds"));
	SpawnBounds->SetBoxExtent(FVector(100, 100, 50));
	SpawnBounds->SetupAttachment(RootComponent);
	SpawnBounds->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SpawnBounds->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnBounds->SetRelativeLocation(FVector(0, 0, 60));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(RootComponent);
	Billboard->SetRelativeLocation(FVector(0, 0, 50));
	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction Arrow"));
	DirectionArrow->SetupAttachment(RootComponent);
	DirectionArrow->SetRelativeLocation(FVector(0, 0, 50));
	SpawnBounds->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	bCanBeDamaged = false;
}

// Called when the game starts or when spawned
void ANPCSpawner::BeginPlay()
{
	Super::BeginPlay();
	NPCData = NPCDataHandle.GetRow<FNPCData>("Getting NPC data for spawner");
	SpawnChild();
}

// Called every frame
void ANPCSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//No child npc, start spawn countdown
	if (!ChildNPC)
	{
		SpawnTimer += DeltaTime;
		if (SpawnTimer > SpawnDelaySeconds)
		{
			SpawnChild();
			SpawnTimer = 0;
		}
	}
}


void ANPCSpawner::SpawnChild_Implementation()
{
	auto box = FBoxCenterAndExtent(GetActorLocation(), SpawnBounds->GetScaledBoxExtent()).GetBox();
	auto spawnLocation = FMath::RandPointInBox(box);
	spawnLocation.Z += 100;
	ChildNPC = GetWorld()->SpawnActor<ABasicNPC>(ABasicNPC::StaticClass(), spawnLocation, GetActorRotation());
	if (ChildNPC)
	{	
		ChildNPC->Setup(NPCData);
		ChildNPC->SpawnDefaultController();
		ChildNPC->DeathDelegate.AddDynamic(this, &ANPCSpawner::ChildDied);
		UE_LOG(LogTemp, Warning, TEXT("NPC Spawned!!"));
	}
}

bool ANPCSpawner::SpawnChild_Validate()
{
	return true;
}

void ANPCSpawner::ChildDied()
{
	ChildNPC = nullptr;
}
