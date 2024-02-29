// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitDenoCommands.h"

#define LOCTEXT_NAMESPACE "FGitDenoModule"

void FGitDenoCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GitDeno", "Execute GitDeno action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
