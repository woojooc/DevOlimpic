// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ResultText.h"

// Sets default values
AWJ_ResultText::AWJ_ResultText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(rootComp);

	winText = CreateDefaultSubobject<USceneComponent>(TEXT("WinTEXT"));
	winText->SetupAttachment(rootComp);
	loseText = CreateDefaultSubobject<USceneComponent>(TEXT("LoseTEXT"));
	loseText->SetupAttachment(rootComp);

	for (int i = 0; i < 3; i++)
	{
		auto name = FString::Printf(TEXT("WinTEXT%02d"), i);
		winTexts.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName(name)));
		winTexts[i]->SetupAttachment(winText);
	}
	for (int i = 0; i < 4; i++)
	{
		auto name = FString::Printf(TEXT("LoseTEXT%02d"), i);
		loseTexts.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName(name)));
		loseTexts[i]->SetupAttachment(loseText);
	}
}

void AWJ_ResultText::ShowWin()
{
	for (int i = 0; i < winTexts.Num(); i++)
	{
		winTexts[i]->SetHiddenInGame(false);
	}
	for (int i = 0; i < loseTexts.Num(); i++)
	{
		loseTexts[i]->SetHiddenInGame(true);
	}
}

void AWJ_ResultText::ShowLose()
{
	for (int i = 0; i < winTexts.Num(); i++)
	{
		winTexts[i]->SetHiddenInGame(true);
	}
	for (int i = 0; i < loseTexts.Num(); i++)
	{
		loseTexts[i]->SetHiddenInGame(false);
	}
}

void AWJ_ResultText::HidQeAll()
{
	for (int i = 0; i < winTexts.Num(); i++)
	{
		winTexts[i]->SetHiddenInGame(true);
	}
	for (int i = 0; i < loseTexts.Num(); i++)
	{
		loseTexts[i]->SetHiddenInGame(true);
	}
}

// Called when the game starts or when spawned
void AWJ_ResultText::BeginPlay()
{
	Super::BeginPlay();
	
}


