// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

UCLASS()
class AEndlessRunnerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void ManualTick(float DeltaSeconds);

	void Setup();
	AEndlessRunnerGameMode();

	UPROPERTY(BlueprintReadWrite)
	bool GameOver; 

	UFUNCTION(BlueprintCallable)
	float GetDifficulty() const;

	UFUNCTION(BlueprintCallable)
	float GetLives() const;
	
	UPROPERTY(EditAnywhere)
	float DifficultyIncreaseSpeed;

	UPROPERTY(BlueprintReadWrite)
	float Score;

	void EndGame();
	void TakeDamages();

	DECLARE_EVENT(FEndlessRunnerGameMode, FOnEndGame);
	FOnEndGame& OnEndGame() { return GameEndEvent; }

private:
	FOnEndGame GameEndEvent;

	float difficulty;
	float lives;
};



