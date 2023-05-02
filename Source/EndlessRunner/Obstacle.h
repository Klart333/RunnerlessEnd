// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerGameMode.h"
#include "ObstacleSpawner.h"
#include "Obstacle.generated.h"

UCLASS()
class ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY(EditAnywhere)
	float DefaultSpeed;

	AObstacleSpawner* Spawner;
	bool beenDodged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float speedMultiplier;
	
	AEndlessRunnerGameMode* GameMode;

public:
	void MoveDown();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpeed(float speed);

	UFUNCTION(BlueprintCallable)
	void Fracture();
};
