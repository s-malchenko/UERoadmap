// Copyright Epic Games, Inc. All Rights Reserved.

#include "UERoadmapGameMode.h"
#include "GameFramework/HUD.h"
#include "UERoadmapCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUERoadmapGameMode::AUERoadmapGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_PlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}
