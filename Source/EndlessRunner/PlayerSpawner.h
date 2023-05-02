// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerCharacter.h"
#include "GameFramework/Actor.h"
#include "PlayerSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API APlayerSpawner : public APawn
{
	GENERATED_BODY()
	
public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// ReSharper disable once UnrealHeaderToolError
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction2;
	
	// Sets default values for this actor's properties
	APlayerSpawner();

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget))
	FVector Positions[2];

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget))
	TSubclassOf<AEndlessRunnerCharacter> Players[2];
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AEndlessRunnerCharacter* spawnedPlayers[2];

	void JumpOne() ;
	void JumpTwo() ;
	void Jump(int index) ;

	void StopJumpOne() ;
	void StopJumpTwo() ;
	void StopJump(int index) ;

	void MoveOne(const FInputActionValue& value);
	void MoveTwo(const FInputActionValue& value);
	void Move(const FInputActionValue& value, int index) ;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
