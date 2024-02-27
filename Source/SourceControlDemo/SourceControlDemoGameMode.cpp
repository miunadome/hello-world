// Copyright Epic Games, Inc. All Rights Reserved.

#include "SourceControlDemoGameMode.h"
#include "SourceControlDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASourceControlDemoGameMode::ASourceControlDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
