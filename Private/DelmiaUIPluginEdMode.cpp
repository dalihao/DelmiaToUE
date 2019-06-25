// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DelmiaUIPluginEdMode.h"
#include "DelmiaUIPluginEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FDelmiaUIPluginEdMode::EM_DelmiaUIPluginEdModeId = TEXT("EM_DelmiaUIPluginEdMode");

FDelmiaUIPluginEdMode::FDelmiaUIPluginEdMode()
{

}

FDelmiaUIPluginEdMode::~FDelmiaUIPluginEdMode()
{

}

void FDelmiaUIPluginEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FDelmiaUIPluginEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FDelmiaUIPluginEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FDelmiaUIPluginEdMode::UsesToolkits() const
{
	return true;
}




