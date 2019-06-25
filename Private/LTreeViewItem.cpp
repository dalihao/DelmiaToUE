// Fill out your copyright notice in the Description page of Project Settings.


#include "LTreeViewItem.h"

void ULTreeViewItem::SetContent(UWidget * Content)
{
	if (!Content)return;
	if (ParentBorder.IsValid())
		ParentBorder->SetContent(Content->TakeWidget());
	else return;
}
