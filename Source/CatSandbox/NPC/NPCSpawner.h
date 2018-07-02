// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicNPC.h"
#include "NPCData.h"
#include "NPCSpawner.generated.h"

UCLASS()
class CATSANDBOX_API ANPCSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	ABasicNPC* ChildNPC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnDelaySeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	FDataTableRowHandle NPCDataHandle;

	FNPCData* NPCData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	class UBoxComponent* SpawnBounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	class UBillboardComponent* Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	class UArrowComponent* DirectionArrow;

	UPROPERTY()
	class USceneComponent* SphereRoot;

	float SpawnTimer = 0.f;
	
	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Spawner")
	void SpawnChild();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void ChildDied();
		
};
