// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XmlParser/Public/XmlParser.h"
#include "MyXmlParserActor.generated.h"

UCLASS()
class DELMIAUIPLUGIN_API AMyXmlParserActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyXmlParserActor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
		FString filePath;
	class FXmlFile* xmlFile;
	TArray<FXmlNode*> reference3DNodes;
	TArray<FXmlNode*> instance3DNodes;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BLueprintCallable, Category = "XmlParser")
		void SetXmlFile(FString inFilePath);

	//UFUNCTION(BlueprintCallable,Category="XmlParser")
	UFUNCTION(BlueprintCallable, Category = "XmlParser")
		FString SetTreeViewContent(TArray<FString>& childrenNode);

	TArray<FString> SetChildrenContent();

	void SetInfo(FXmlNode* rootNode);

	virtual FString SetIdBlock(FXmlNode* rootNode);

	virtual FString SetName(FXmlNode* rootNode);

};
