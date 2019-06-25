// Fill out your copyright notice in the Description page of Project Settings.


#include "MyXmlParserActor.h"

// Sets default values
AMyXmlParserActor::AMyXmlParserActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//xmlFile = new FXmlFile("D:/UEProject/TestDelmiaToUE/DelmiaToUE/TestMesh/fbx.FBXXml");
	xmlFile = new FXmlFile("C:/test.xml");
}

// Called when the game starts or when spawned
void AMyXmlParserActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyXmlParserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyXmlParserActor::SetXmlFile(FString inFilePath)
{
	xmlFile = new FXmlFile(inFilePath);
}

FString AMyXmlParserActor::SetTreeViewContent(TArray<FString>& nodeChildrenName)
{
	FString name;
	
	// TODO: 在此处插入 return 语句
	FXmlNode* rootNode = xmlFile->GetRootNode();
	TArray<FXmlNode*> rootNodeChildren = rootNode->GetChildrenNodes();
	int i = 0;
	for (; i < rootNodeChildren.Num(); i++)
	{
		if (rootNodeChildren[i]->GetTag() == "ProductStructure")
		{
 			const TArray<FXmlNode*> productChildren = rootNodeChildren[i]->GetChildrenNodes();
			const TArray<FXmlAttribute> productChildrenAttribute = productChildren[0]->GetAttributes();
			for (auto Iter = productChildrenAttribute.CreateConstIterator(); Iter; Iter++)
			{
				if (Iter->GetTag() == "name")
				{
					const FString value=Iter->GetValue();
					name = value;
				}
			}
			break;
		}
	}
	SetInfo(rootNodeChildren[i]);
	nodeChildrenName= SetChildrenContent();

	return name;
}

TArray<FString> AMyXmlParserActor::SetChildrenContent()
{
	TArray<FString> childrenContent;
	for (int i = 0; i < instance3DNodes.Num(); i++)
	{
		
		childrenContent.Add(SetIdBlock(instance3DNodes[i])+ SetName(instance3DNodes[i]));
				
	}
	
	
	return childrenContent;
}

void AMyXmlParserActor::SetInfo(FXmlNode * rootNode)
{
	
	if (rootNode->GetNextNode() != nullptr)
	{
		const TArray<FXmlNode*> rootChildrenNode = rootNode->GetChildrenNodes();
		for (int i = 0; i < rootChildrenNode.Num(); i++)
		{
			if (rootChildrenNode[i]->GetTag() == "Reference3D")
			{
				reference3DNodes.Add(rootChildrenNode[i]);
			}
			if (rootChildrenNode[i]->GetTag() == "Instance3D")
			{
				instance3DNodes.Add(rootChildrenNode[i]);
			}
		}
	}
	
	
}

FString AMyXmlParserActor::SetIdBlock(FXmlNode * rootNode)
{
	TArray<FXmlNode*> instance3DNodeChildren;
	instance3DNodeChildren = rootNode->GetChildrenNodes();
	for (int i = 0; i < instance3DNodeChildren.Num(); i++)
	{
		if ("IsInstanceOf" == instance3DNodeChildren[i]->GetTag())
		{
			FString content = instance3DNodeChildren[i]->GetContent();
			for (int j = 1; j < reference3DNodes.Num(); j++)
			{
				if (content == reference3DNodes[j]->GetAttribute("id"))
				{
					return (reference3DNodes[j]->GetAttribute("name"));
				}
			}
		}
	}
	return FString();
}

FString AMyXmlParserActor::SetName(FXmlNode * rootNode)
{
	FString nameAttribute = rootNode->GetAttribute("name");
	FString outString;
	outString = FString("(").Append(nameAttribute.Append(")"));
	return outString;
}

