// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SingleModeInfo.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h"
#include "SJ_SingleMode.h"

// Sets default values
ASJ_SingleModeInfo::ASJ_SingleModeInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	infoText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InfoText"));
	infoText->SetupAttachment(rootComp);
	infoText->SetWorldSize(20);
	infoText->SetHorizontalAlignment(EHTA_Center);
	infoText->SetVerticalAlignment(EVRTA_TextCenter);
	infoText->SetText(FText::FromString("ServeMode"));

}

// Called when the game starts or when spawned
void ASJ_SingleModeInfo::BeginPlay()
{
	Super::BeginPlay();
	
	singleMode = Cast<ASJ_SingleMode>(GetWorld()->GetAuthGameMode());
}

//void ASJ_SingleModeInfo::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ASJ_SingleModeInfo::SetInfo()
{
	if (singleMode->mode_State == ESingleModeType::Serve)
	{
		infoText->SetText(FText::FromString("ServeMode"));
	}
	else if (singleMode->mode_State == ESingleModeType::Recieve)
	{
		infoText->SetText(FText::FromString("ReceiveMode"));
	}
}

