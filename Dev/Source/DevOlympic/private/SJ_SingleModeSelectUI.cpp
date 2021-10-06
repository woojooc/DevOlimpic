// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SingleModeSelectUI.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "SJ_SingleMode.h"

void USJ_SingleModeSelectUI::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Serve->OnClicked.AddDynamic(this, &USJ_SingleModeSelectUI::ServeMode);
	Btn_Receive->OnClicked.AddDynamic(this, &USJ_SingleModeSelectUI::RecieveMode);
}

void USJ_SingleModeSelectUI::ServeMode()
{
	auto singleMode = Cast<ASJ_SingleMode>(GetWorld()->GetAuthGameMode());

	singleMode->currentTime = 0;
	singleMode->mode_State = ESingleModeType::Serve;
}

void USJ_SingleModeSelectUI::RecieveMode()
{
	auto singleMode = Cast<ASJ_SingleMode>(GetWorld()->GetAuthGameMode());

	singleMode->currentTime = 0;
	singleMode->mode_State = ESingleModeType::Recieve;
}
