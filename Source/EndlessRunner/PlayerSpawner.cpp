// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpawner.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerSpawner::APlayerSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpawner::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
    	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    	{
    		Subsystem->AddMappingContext(DefaultMappingContext, 0);
    	}
    }
	
	UWorld* world = GetWorld();
	if (world)
	{
		for	(int i = 0; i < 2; i++)
		{
			FVector pos = GetActorLocation() + Positions[i];
			FRotator rot = FRotator(0, 180, 0);

			TSubclassOf<AEndlessRunnerCharacter> player = Players[i];
			if (player)
			{
				spawnedPlayers[i] = world->SpawnActor<AEndlessRunnerCharacter>(player, pos, rot);
			}
		}
	}
}

void APlayerSpawner::JumpOne() 
{
	Jump(0);
}

void APlayerSpawner::JumpTwo() 
{
	Jump(1);
}

void APlayerSpawner::Jump(int index) 
{
	spawnedPlayers[index]->Jump();
}

void APlayerSpawner::StopJumpOne() 
{
	StopJump(0);
}

void APlayerSpawner::StopJumpTwo() 
{
	StopJump(1);
}

void APlayerSpawner::StopJump(int index) 
{
	spawnedPlayers[index]->StopJumping();
}

void APlayerSpawner::MoveOne(const FInputActionValue& value)
{
	Move(value, 0);
}

void APlayerSpawner::MoveTwo(const FInputActionValue& value)
{
	Move(value, 1);
}

void APlayerSpawner::Move(const FInputActionValue& value, int index) 
{
	spawnedPlayers[index]->SideStep(value.GetMagnitude());
}

// Called every frame
void APlayerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerSpawner::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerSpawner::JumpOne);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerSpawner::StopJumpOne);

		EnhancedInputComponent->BindAction(JumpAction2, ETriggerEvent::Triggered, this, &APlayerSpawner::JumpTwo);
		EnhancedInputComponent->BindAction(JumpAction2, ETriggerEvent::Completed, this, &APlayerSpawner::StopJumpTwo);
		
		//Side Stepping
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerSpawner::MoveOne);
		EnhancedInputComponent->BindAction(MoveAction2, ETriggerEvent::Started, this, &APlayerSpawner::MoveTwo);
	}
}

