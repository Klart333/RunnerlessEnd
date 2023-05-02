// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"

#include "EndlessRunnerGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AEndlessRunnerCharacter

AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.0f;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 0.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AEndlessRunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Jump();

	locked = false;

	GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAAAAHHH!"));
		return;
	}

	GameMode->OnEndGame().AddUObject(this, &AEndlessRunnerCharacter::LockInput);
}

void AEndlessRunnerCharacter::TakeSomeDamage()
{
	if (GameMode)
	{
		GameMode->TakeDamages();
	}
}
//////////////////////////////////////////////////////////////////////////
// Input

void AEndlessRunnerCharacter::LockInput()
{
	locked = true;
}


void AEndlessRunnerCharacter::SideStep(const float value)
{
	if (locked)
	{
		return;
	}

	FVector pos = GetActorLocation();
	if (pos.Y + 300 * -value > 350 || pos.Y + 300 * -value < -350)
	{
		return;
	}
	 
	SetActorLocation(pos + FVector::LeftVector * 300 * value);
}

void AEndlessRunnerCharacter::Jump()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Jump"));

	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;

	Super::Jump();
}




