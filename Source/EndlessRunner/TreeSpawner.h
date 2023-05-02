// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerGameMode.h"
#include "TreeSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API ATreeSpawner : public AActor
{ 
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeSpawner();

	UPROPERTY(EditAnywhere)
	float SpawnRange = 100;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Tree;

	UPROPERTY(EditAnywhere)
	float SpawnRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AEndlessRunnerGameMode* GameMode;

	float timer;

public:
	void SpawnTree();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
