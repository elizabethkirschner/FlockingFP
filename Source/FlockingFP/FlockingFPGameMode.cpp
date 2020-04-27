// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FlockingFPGameMode.h"
#include "FlockingFPHUD.h"
#include "FlockingFPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFlockingFPGameMode::AFlockingFPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFlockingFPHUD::StaticClass();
}
