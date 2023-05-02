// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputPriority = 1000;
}
