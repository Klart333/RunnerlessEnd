// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawner.h"

#include "EndlessRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATreeSpawner::ATreeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

}

// Called when the game starts or when spawned
void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAAAAHHH!"));
	}
}

void ATreeSpawner::SpawnTree()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FVector pos = GetActorLocation() + FVector::RightVector * FMath::RandRange(-SpawnRange, SpawnRange);
		FRotator rot = FRotator();
		
		world->SpawnActor<AActor>(Tree, pos, rot);
	}
}

// Called every frame
void ATreeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	timer += DeltaTime;

	if (timer >= 1.0f / (SpawnRate * GameMode->GetDifficulty()))
	{
		timer = 0;
		SpawnTree();
	}
}

