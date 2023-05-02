// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameMode.h"
#include "Obstacle.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	beenDodged = false;
	speedMultiplier = 1;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAAAAHHH!"));
	}
}

void AObstacle::MoveDown()
{
	FVector pos = GetActorLocation();
	pos += FVector::ForwardVector * DefaultSpeed * speedMultiplier;

	if (pos.X > 0 && !beenDodged)
	{
		if (Spawner)
		{
			beenDodged = true;
			Spawner->ObstacleDodged();
		}
	}
	else if (pos.X > 1000)
	{
		Destroy();
		return;
	}
	
	SetActorLocation(pos);
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode)
	{
		SetSpeed(GameMode->GetDifficulty());
	}
	
	MoveDown();
}

void AObstacle::SetSpeed(float speed)
{
	speedMultiplier = speed;
}

void AObstacle::Fracture()
{
		
}

