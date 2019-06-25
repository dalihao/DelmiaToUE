// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/*UMG*/
#include "Runtime/UMG/Public/UMG.h"
/*****/


#include "SLTreeView.h"


#include "Components/Widget.h"
#include "LTreeView.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTreeViewOnSelectChange, ULTreeViewItem *, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTreeViewOnSelectChange, ULTreeViewItem *, Item);
/**
 * 
 */
UCLASS()
class DELMIAUIPLUGIN_API ULTreeView : public UWidget
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FTreeViewOnSelectChange	OnSelectChangeEvent;



public:

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void OnSelectChanged(ULTreeViewItem * Item);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		bool IsItemExpanded(ULTreeViewItem * Item);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void SelectDirectory(ULTreeViewItem * CategoryToSelect);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		ULTreeViewItem * GetSelectDirectory();

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		TSet<ULTreeViewItem*>GetExpandedItems();

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		ULTreeViewItem * AddRootDir(FString Dir, UWidget * CustomWidget);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		ULTreeViewItem * AddSubDir(ULTreeViewItem * ParentCategory, FString Dir, UWidget * CustomWidget);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void RemoveItem(ULTreeViewItem * Item, bool bRebuild);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		bool Rebuild();

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		bool ClearAll(bool bRebuild);

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void SetItemExpansion(ULTreeViewItem * InItem, bool InShouldExpandItem)
	{
		if (MyTreeView.IsValid())
		{
			MyTreeView->SetItemExpansion(InItem, InShouldExpandItem);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void SetSingleExpandedItem(ULTreeViewItem * InItem)
	{
		if (MyTreeView.IsValid())
		{
			MyTreeView->SetSingleExpandedItem(InItem);
		}

	}

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		bool IsItemSelected(ULTreeViewItem* InItem) const
	{
		if (InItem->IsValidLowLevel())
		{
			return MyTreeView->IsItemSelected(InItem);
		}
		return false;
	}

	UFUNCTION(BlueprintCallable, Category = "TreeView")
		void SetItemHeight(float Height)
	{
		if (MyTreeView.IsValid())
		{
			MyTreeView->SetItemHeight(Height);
		}

	}

protected:
	virtual TSharedRef<SWidget>RebuildWidget()override;
	virtual void OnBindingChanged(const FName& Property)override;

	TSharedPtr<SLTreeView> MyTreeView;

};
