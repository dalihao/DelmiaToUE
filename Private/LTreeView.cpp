// Fill out your copyright notice in the Description page of Project Settings.


#include "LTreeView.h"

ULTreeView::ULTreeView(const FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	bIsVariable = false;
}

void ULTreeView::OnSelectChanged(ULTreeViewItem * Item)
{
	OnSelectChangeEvent.Broadcast(Item);//call 
}

bool ULTreeView::IsItemExpanded(ULTreeViewItem * Item)
{
	if (MyTreeView.IsValid())
	{
		return MyTreeView->IsItemExpanded(Item);
	}
	return false;
}

void ULTreeView::SelectDirectory(ULTreeViewItem * CategoryToSelect)
{
	if (MyTreeView.IsValid())
	{
		MyTreeView->SelectDirectory(CategoryToSelect);
	}

}

ULTreeViewItem * ULTreeView::GetSelectDirectory()
{
	if (MyTreeView.IsValid())
	{
		return MyTreeView->GetSelectedDirectory();
	}

	return nullptr;
}

TSet<ULTreeViewItem*> ULTreeView::GetExpandedItems()
{
	TSet<ULTreeViewItem*>Local_ExpendedItems;
	if (MyTreeView.IsValid())
	{
		MyTreeView->GetExpandedItems(Local_ExpendedItems);

		return Local_ExpendedItems;
	}
	return Local_ExpendedItems;
}

ULTreeViewItem * ULTreeView::AddRootDir(FString Dir, UWidget * CustomWidget)
{
	if (MyTreeView.IsValid())
	{
		return MyTreeView->AddRootDirectory(Dir, CustomWidget);
	}
	return nullptr;
}

void ULTreeView::RemoveItem(ULTreeViewItem * Item, bool bRebuild)
{
	if (MyTreeView.IsValid())
	{
		MyTreeView->RemoveItem(Item, bRebuild);
	}

}

bool ULTreeView::Rebuild()
{
	if (MyTreeView.IsValid())
	{
		MyTreeView->RebuildTree();
		return true;
	}
	return false;
}

bool ULTreeView::ClearAll(bool bRebuild)
{
	if (MyTreeView.IsValid())
	{
		MyTreeView->Clear();
		if (bRebuild)
		{
			Rebuild();
		}
		return true;
	}
	return false;
}

TSharedRef<SWidget> ULTreeView::RebuildWidget()
{
	MyTreeView = SNew(SLTreeView)
		;
	if (MyTreeView.IsValid())
	{
		MyTreeView->OnSelectChangedDelegate.BindUFunction(this, FName("OnSelectChanged"));//
	}
	return MyTreeView.ToSharedRef();
}

void ULTreeView::OnBindingChanged(const FName & Property)
{
	Super::OnBindingChanged(Property);

}

ULTreeViewItem * ULTreeView::AddSubDir(ULTreeViewItem * ParentCategory, FString Dir, UWidget * CustomWidget)
{
	if (MyTreeView.IsValid())
	{
		return MyTreeView->AddSubDirectory(ParentCategory, Dir, CustomWidget);
	}
	return nullptr;
}
