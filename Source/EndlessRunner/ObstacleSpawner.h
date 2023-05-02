// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameMode.h"

#include "Containers/Array.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class AObstacle;

UCLASS()
class ENDLESSRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget))
	FVector Lanes[3];
	
	UPROPERTY(EditInstanceOnly )
	TArray<TSubclassOf<AObstacle>> Obstacles;

	UPROPERTY(EditAnywhere)
	float SpawnRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float timer;

	AEndlessRunnerGameMode* GameMode;

	TArray<AObstacle*> SpawnedObstacles;

public:
	void SpawnObstacle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ObstacleDodged(); 
};
