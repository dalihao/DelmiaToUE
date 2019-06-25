// Fill out your copyright notice in the Description page of Project Settings.


#include "SLTreeView.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLTreeView::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/

	RebuildTree();

	LTreeViewWiget =
		SNew(STreeViewObj)
		.SelectionMode(ESelectionMode::Single)
		.ClearSelectionOnClick(false)
		.TreeItemsSource(&Directories)
		.OnGenerateRow(this, &SLTreeView::LTree_OnGenerateRow)
		.OnGetChildren(this, &SLTreeView::LTree_OnGetChildren)
		.OnSelectionChanged(this, &SLTreeView::LTree_OnSelectionChanged)

		;
	ChildSlot.AttachWidget(LTreeViewWiget.ToSharedRef());

}
SLTreeView::~SLTreeView()
{


}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
ULTreeViewItem * SLTreeView::GetSelectedDirectory() const
{
	if (LTreeViewWiget.IsValid())
	{
		auto SelectedItems = LTreeViewWiget->GetSelectedItems();
		if (SelectedItems.Num() > 0)
		{
			const auto & SelectedCategoryItem = SelectedItems[0];
			return SelectedCategoryItem;
		}
	}
	return NULL;

}

void SLTreeView::SelectDirectory(ULTreeViewItem * CategoryToSelect)
{
	if (ensure(LTreeViewWiget.IsValid()))
	{
		LTreeViewWiget->SetSelection(CategoryToSelect);
	}
}

bool SLTreeView::IsItemExpanded(ULTreeViewItem * Item) const
{
	if (Item->IsValidLowLevel())
	{
		return LTreeViewWiget->IsItemExpanded(Item);
	}
	else
	{
		return false;
	}

}

TSharedRef<ITableRow> SLTreeView::LTree_OnGenerateRow(ULTreeViewItem * Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	/////////////////////Debug/////////////////////////////

	if (!Item->IsValidLowLevel())
	{
		return SNew(STableRow<ULTreeViewItem * >, OwnerTable)
			[
				SNew(STextBlock)
				.Text(FText::FromString("有BUG了！！！"))
			.ColorAndOpacity(FLinearColor::Red)
			];
	}
	if (!Item->CustomWidget->IsValidLowLevel())
	{
		return SNew(STableRow<ULTreeViewItem * >, OwnerTable)
			[
				SNew(STextBlock)
				.Text(FText::FromString("有BUG了！！！"))
			.ColorAndOpacity(FLinearColor::Red)
			];
	}
	return SNew(STableRow<ULTreeViewItem * >, OwnerTable)
		[
			SAssignNew(Item->ParentBorder, SBorder)
			.BorderBackgroundColor(FSlateColor(FLinearColor(0, 0, 0, 0)))
		[
			Item->CustomWidget->TakeWidget()
		]

		];


}

void SLTreeView::LTree_OnGetChildren(ULTreeViewItem * Item, TArray<ULTreeViewItem*>& OutChildren)
{
	//const auto & SubCategories = ??????;

	if (Item->IsValidLowLevel())
	{
		OutChildren.Append(Item->SubDirectories);
	}
	else
	{
		return;
	}

}

void SLTreeView::LTree_OnSelectionChanged(ULTreeViewItem * Item, ESelectInfo::Type SelectInfo)
{
	if (Item->IsValidLowLevel())
		OnSelectChangedDelegate.ExecuteIfBound(*Item);
	else return;


}

void SLTreeView::RebuildTree()
{
	if (LTreeViewWiget.IsValid())
	{
		LTreeViewWiget->RequestTreeRefresh();
	}
}

void SLTreeView::Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

void SLTreeView::GetExpandedItems(TSet<ULTreeViewItem*>& ExpandedItems)
{
	if (LTreeViewWiget.IsValid())
	{
		LTreeViewWiget->GetExpandedItems(ExpandedItems);
	}

}

ULTreeViewItem * SLTreeView::AddRootDirectory(FString Dir, UWidget * Widget)
{

	ULTreeViewItem * AddRoot = NewObject<ULTreeViewItem>(ULTreeViewItem::StaticClass());
	AddRoot->ParentDir = nullptr;
	AddRoot->DirectoryPath = Dir;

	AddRoot->CustomWidget = Widget;

	AddRoot->AddToRoot();
	//Widget->AddToRoot();

	Directories.Add(AddRoot);

	return AddRoot;


}

ULTreeViewItem * SLTreeView::AddSubDirectory(ULTreeViewItem * ParentCategory, FString Dir, UWidget * Widget)
{
	ULTreeViewItem * AddSub = NewObject<ULTreeViewItem>(ULTreeViewItem::StaticClass());
	AddSub->ParentDir = ParentCategory;
	AddSub->DirectoryPath = Dir;
	AddSub->CustomWidget = Widget;

	AddSub->AddToRoot();
	//Widget->AddToRoot();

	ParentCategory->AddSubDirectory(AddSub);
	return AddSub;


}

void SLTreeView::RemoveItem(ULTreeViewItem * Item, bool bRebuild)
{

	if (Item->ParentDir == NULL)
	{
		Directories.Remove(Item);

	}
	else
	{
		Item->ParentDir->SubDirectories.Remove(Item);
	}

	Item->ConditionalBeginDestroy();

	if (bRebuild)
	{
		RebuildTree();
	}


}

TArray<ULTreeViewItem*> SLTreeView::GetAllDirectory()
{

	return Directories;

}

void SLTreeView::Clear()
{
	for (int32 i = 0; i < Directories.Num(); ++i)
	{
		Directories[i]->ConditionalBeginDestroy();
	}

	Directories.Empty();

}

void SLTreeView::SetItemExpansion(ULTreeViewItem * InItem, bool InShouldExpandItem)
{

	if (LTreeViewWiget.IsValid() && InItem->IsValidLowLevel())
	{
		LTreeViewWiget->SetItemExpansion(InItem, InShouldExpandItem);
	}

}

void SLTreeView::SetSingleExpandedItem(ULTreeViewItem * InItem)
{
	if (LTreeViewWiget.IsValid() && InItem->IsValidLowLevel())
	{
		LTreeViewWiget->SetSingleExpandedItem(InItem);
	}

}
