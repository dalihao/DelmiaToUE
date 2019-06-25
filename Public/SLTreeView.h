// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LTreeViewItem.h"
#include "STreeView.h"

#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnSelectChanged, ULTreeViewItem&);

typedef STreeView<ULTreeViewItem * >STreeViewObj;

/**
 *
 */
class DELMIAUIPLUGIN_API SLTreeView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLTreeView)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
		void Construct(const FArguments& InArgs);

	/*destructor*/
	~SLTreeView();

	FOnSelectChanged OnSelectChangedDelegate;

	ULTreeViewItem * GetSelectedDirectory()const;

	void SelectDirectory(ULTreeViewItem * CategoryToSelect);

	bool IsItemExpanded(ULTreeViewItem * Item)const;

public:

	TSharedRef<ITableRow>LTree_OnGenerateRow(ULTreeViewItem * Item, const TSharedRef<STableViewBase>&OwnerTable);

	void LTree_OnGetChildren(ULTreeViewItem * Item, TArray<ULTreeViewItem*>&OutChildren);

	void LTree_OnSelectionChanged(ULTreeViewItem * Item, ESelectInfo::Type SelectInfo);

	void RebuildTree();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)override;

	void GetExpandedItems(TSet<ULTreeViewItem*>&ExpandedItems);

	ULTreeViewItem * AddRootDirectory(FString Dir, UWidget * Widget);

	ULTreeViewItem * AddSubDirectory(ULTreeViewItem * ParentCategory, FString Dir, UWidget * Widget);

	void RemoveItem(ULTreeViewItem * Item, bool bRebuild);

	TArray<ULTreeViewItem *>GetAllDirectory();

	void Clear();

	void SetItemExpansion(ULTreeViewItem * InItem, bool InShouldExpandItem);

	void SetSingleExpandedItem(ULTreeViewItem * InItem);

	bool IsItemSelected(ULTreeViewItem* InItem) const
	{
		if (InItem->IsValidLowLevel())
		{
			return LTreeViewWiget->IsItemSelected(InItem);
		}
		return false;
	}

	void SetItemHeight(float Height)
	{
		if (LTreeViewWiget.IsValid())
		{
			LTreeViewWiget->SetItemHeight(Height);
		}

	}







protected:

	TArray<ULTreeViewItem * >Directories;

private:

	TSharedPtr<STreeViewObj>LTreeViewWiget;



};
