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
}

void AWJ_ResultText::ShowWin()
{
	winText->SetHiddenInGame(false);
	loseText->SetHiddenInGame(true);
}

void AWJ_ResultText::ShowLose()
{
	winText->SetHiddenInGame(true);
	loseText->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void AWJ_ResultText::BeginPlay()
{
	Super::BeginPlay();
	
}


