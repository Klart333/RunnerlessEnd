// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AEndlessRunnerGameMode::Setup()
{
	DifficultyIncreaseSpeed = 0.05f;
	difficulty = 1;
	GameOver = false;
	lives = 3;
}

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	Setup();
}

float AEndlessRunnerGameMode::GetDifficulty() const
{
	return difficulty;
}

float AEndlessRunnerGameMode::GetLives() const
{
	return lives;
}

void AEndlessRunnerGameMode::EndGame()
{
	difficulty = 0;
	DifficultyIncreaseSpeed = 0;
	GameOver = true;
	GameEndEvent.Broadcast();
}

void AEndlessRunnerGameMode::TakeDamages()
{
	lives--;

	if (lives <= 0)
	{
		EndGame();
	}
}

void AEndlessRunnerGameMode::ManualTick(float DeltaTime) // For some reason I could not get the inherited tick to work, no matter what
{
	Super::Tick(DeltaTime);

	difficulty += DeltaTime * DifficultyIncreaseSpeed;
}
