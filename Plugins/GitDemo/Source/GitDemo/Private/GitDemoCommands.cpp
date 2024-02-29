// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitDemoCommands.h"

#define LOCTEXT_NAMESPACE "FGitDemoModule"

void FGitDemoCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GitDemo", "Bring up GitDemo window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
