// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameMode.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EndlessRunnerCharacter.generated.h"


UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	///** Follow camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* FollowCamera;

public:
	AEndlessRunnerCharacter();

	UFUNCTION(BlueprintCallable)
	void TakeSomeDamage();
	void LockInput();

	void SideStep(const float value);

	virtual void Jump() override;

protected:
	
			
	AEndlessRunnerGameMode* GameMode;
	
	// To add mapping context
	virtual void BeginPlay();

	bool locked;
};

