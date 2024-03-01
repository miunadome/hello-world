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
	currentTag = FGitHelper::GetCurrentTag();
	// 转换为TSharedPtr数组
	for (auto& Branch : branches)
	{
		SharedBranches.Add(MakeShareable(new FString(Branch)));
	}

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

	FText Tag = FText::Format(
		LOCTEXT("currenttag", "Tag: {0} "),
		FText::FromString(currentTag)
	);
	//FText branch = FText::Format(
	//	LOCTEXT("currentbranch", "branch: {0} "),
	//	FText::FromString(currentTag)
	//);
	// 
	//FText branch = FText::Format(
	//	LOCTEXT("currentbranch", "branch: {0} "),
	//	FText::FromString(currentTag)
	//);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight()[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()[
					SNew(STextBlock).Text(Tag)
				]
				//+ SHorizontalBox::Slot()[
				//	SNew(SListView< TSharedPtr<FString> >).ListItemsSource(&SharedBranches)
				//		.OnGenerateRow(this, &FGitDemoModule::OnGenerateRow)
				//]
				+ SHorizontalBox::Slot()[
					SNew(SComboBox<TSharedPtr<FString>>)
						.OptionsSource(&SharedBranches) // 设置数据源
						.OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
							{
								return SNew(STextBlock).Text(FText::FromString(*Item));
							})
					//	.OnSelectionChanged_Lambda([](TSharedPtr<FString> NewValue, ESelectInfo::Type Type)
					//		{
					//			OnComboBoxSelectionChanged(NewValue, Type);
					//		})
					//	[
					//		SNew(STextBlock).Text_Lambda([SharedBranches ]()
					//			{
					//				return FText::FromString(*CurrentSelection);
					//			})
					//	]

					//CreateComboBoxWithLambda(SharedBranches)



				//		.OnSelectionChanged_Lambda([](TSharedPtr<FString> NewValue, ESelectInfo::Type Type)
				//			{
				//				OnComboBoxSelectionChanged(NewValue, Type);
				//			})
				//				.[
				//					SNew(STextBlock).Text_Lambda([CurrentSelection]()
				//						{
				//							return FText::FromString(*CurrentSelection);
				//						})
				//				];
				//]
				]]
		];
}

TSharedRef<ITableRow> FGitDemoModule::OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
		.Content()
		[
			SNew(STextBlock).Text(FText::FromString(*Item))
		];
}



TSharedRef<SWidget> FGitDemoModule::CreateComboBoxWithLambda(TArray<TSharedPtr<FString>> Items)
{
    // 当前选中项，默认为数组的第一个元素
    //TSharedPtr<FString> CurrentSelection = Items[0];
    TSharedPtr<FString> CurrentSelection = Items[0];

    // 创建下拉框
    return SNew(SComboBox<TSharedPtr<FString>>)
        .OptionsSource(&Items)
        .OnGenerateWidget_Lambda([](TSharedPtr<FString> Item) -> TSharedRef<SWidget>
        {
            return SNew(STextBlock).Text(FText::FromString(*Item));
        })
   //     .OnSelectionChanged_Lambda([&CurrentSelection](TSharedPtr<FString> NewValue, ESelectInfo::Type Type)
   //     {
   //         if (NewValue)
   //         {
   //             CurrentSelection = NewValue;
   //             // 在这里处理选择变化，例如更新UI或者逻辑
   //         }
			//})
;

        //.InitiallySelectedItem(CurrentSelection)
        //[
        //    SNew(STextBlock)
        //    .Text_Lambda([CurrentSelection]() -> FText
        //    {
        //        return FText::FromString(*CurrentSelection);
        //    })
        //];

			//.InitiallySelectedItem(CurrentSelection)
			//// 使用SComboBox的Content方法来动态更新显示文本
			////.Content()
			//[
			//	SNew(STextBlock).Text(FText::FromString(*CurrentSelection))
			//		//.Text_Lambda([&CurrentSelection]() -> FText
			//		//	{
			//		//		if (CurrentSelection.IsValid())
			//		//		{
			//		//			return FText::FromString(*CurrentSelection);
			//		//		}
			//		//		return FText::GetEmpty(); // 当无有效选择时显示空文本
			//		//	})
			//];
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