// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GitDenoStyle.h"

class FGitDenoCommands : public TCommands<FGitDenoCommands>
{
public:

	FGitDenoCommands()
		: TCommands<FGitDenoCommands>(TEXT("GitDeno"), NSLOCTEXT("Contexts", "GitDeno", "GitDeno Plugin"), NAME_None, FGitDenoStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
