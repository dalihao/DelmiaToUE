// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "SBorder.h"
#include "Widget.h"

#include "LTreeViewItem.generated.h"

/**
 * 
 */
UCLASS()
class DELMIAUIPLUGIN_API ULTreeViewItem : public UObject
{
	GENERATED_BODY()

public:

	ULTreeViewItem* ParentDir;
	FString DirectoryPath;
	TArray<ULTreeViewItem*> SubDirectories;
	TSharedPtr<SBorder> ParentBorder;
	UWidget* CustomWidget;
public:

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		ULTreeViewItem * GetParentCatrgory()const
	{
		return ParentDir;
	}

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		FString GetDirectoryPath()const
	{
		return DirectoryPath;
	}
	UFUNCTION(BlueprintCallable, Category = "TreeView")
		TArray<ULTreeViewItem * >GetSubDirectories()const
	{
		return SubDirectories;
	}
	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void SetContent(UWidget * Content);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void AddSubDirectory(ULTreeViewItem * NewSubDir)
	{
		SubDirectories.Add(NewSubDir);
	}

};
