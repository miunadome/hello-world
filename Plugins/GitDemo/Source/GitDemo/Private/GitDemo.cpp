// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitDemo.h"
#include "GitDemoStyle.h"
#include "GitDemoCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName GitDemoTabName("GitDemo");

#define LOCTEXT_NAMESPACE "FGitDemoModule"

void FGitDemoModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGitDemoStyle::Initialize();
	FGitDemoStyle::ReloadTextures();

	FGitDemoCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGitDemoCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FGitDemoModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGitDemoModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GitDemoTabName, FOnSpawnTab::CreateRaw(this, &FGitDemoModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FGitDemoTabTitle", "GitDemo"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	branches = FGitHelper::GetBranches();
	remoteHosts = FGitHelper::GetRemoteHosts();

}

void FGitDemoModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGitDemoStyle::Shutdown();

	FGitDemoCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GitDemoTabName);
}

TSharedRef<SDockTab> FGitDemoModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FGitDemoModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("GitDemo.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FGitDemoModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(GitDemoTabName);
}

void FGitDemoModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGitDemoCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGitDemoCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGitDemoModule, GitDemo)