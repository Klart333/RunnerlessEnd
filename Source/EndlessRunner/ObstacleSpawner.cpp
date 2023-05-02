// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Obstacle.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnedObstacles = TArray<AObstacle*>();
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAAAAHHH!"));
	}
}

void AObstacleSpawner::SpawnObstacle()
{
	UWorld* world = GetWorld();
	if (world)
	{
		int index = FMath::RandRange(0, 2);
		FVector pos = GetActorLocation() + Lanes[index];
		FRotator rot = FRotator();

		int obstacleIndex = FMath::RandRange(0, Obstacles.Num() - 1);
		TSubclassOf<AObstacle> obstacle = Obstacles[obstacleIndex];
		if (obstacle)
		{
			AObstacle* obs = world->SpawnActor<AObstacle>(obstacle, pos, rot);
			obs->Spawner = this;

			SpawnedObstacles.Add(obs);
		}
	}
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;

	if (timer >= 1.0f / (SpawnRate * GameMode->GetDifficulty()))
	{
		timer = 0;
		SpawnObstacle();
	}

	if (GameMode)
	{
		GameMode->ManualTick(DeltaTime);
	}
}

void AObstacleSpawner::ObstacleDodged()
{
	int num = rand() % 10;

	SpawnedObstacles.RemoveAt(0);

	if (num == 0 && SpawnedObstacles.Num() > 1)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Destroyed"));
		SpawnedObstacles[SpawnedObstacles.Num() - 1]->Destroy();
	}
}

