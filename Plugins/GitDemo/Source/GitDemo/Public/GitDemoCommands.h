// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GitDemoStyle.h"

class FGitDemoCommands : public TCommands<FGitDemoCommands>
{
public:

	FGitDemoCommands()
		: TCommands<FGitDemoCommands>(TEXT("GitDemo"), NSLOCTEXT("Contexts", "GitDemo", "GitDemo Plugin"), NAME_None, FGitDemoStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};