// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct GitReturn
{
	bool bSuccessful;
	FString consoleReturn;
};

class FGitHelper
{
public:
	/** Execute Windows Shell command **/
	static FString ExecuteWindowsCommand(FString command);
	/** Get all branches of the current repo **/
	static TArray<FString> GetBranches();
	/** Get all remote hosts of the current repo **/
	static TArray<FString> GetRemoteHosts();
	/** Check if a folder is a git repo **/
	static bool IsGitRepo(FString path);
	/** Push Git Commit to repo **/
	static GitReturn PushCommit(FString remoteHostName, FString destinationBranch);
	/** Get current tag **/
	static FString GetCurrentTag();
	/** Get current branch **/
	static FString GetCurrentBranch();
	/** Checkout Branch **/
	static GitReturn CheckoutBranch(FString Branch = "aaa");



	///** Force push **/
	//static GitReturn ForcePush(FString Branch = "aaa");


};