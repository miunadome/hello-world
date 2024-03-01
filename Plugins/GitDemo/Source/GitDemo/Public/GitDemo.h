// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "GitHelper.h"

class FToolBarBuilder;
class FMenuBuilder;

class FGitDemoModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();


	/** All branches - collected at begin of editor startup **/
	TArray<FString> branches;

	/** All remote hosts - also collected at begin of editor startup **/
	TArray<FString> remoteHosts;

	FString currentTag;
	FString currentBranch;
	TArray<TSharedPtr<FString>> SharedBranches; // 用于SListView的数据


	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);
	TSharedRef<SWidget> CreateComboBoxWithLambda(TArray<TSharedPtr<FString>>);
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
