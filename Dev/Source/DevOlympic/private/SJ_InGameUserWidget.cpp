// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_InGameUserWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void USJ_InGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Btn_Lobby->OnClicked.AddDynamic(this, &USJ_InGameUserWidget::ClickLobby);
	Btn_Quit->OnClicked.AddDynamic(this, &USJ_InGameUserWidget::ClickQuit);
}

void USJ_InGameUserWidget::ClickLobby()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Lobby");
}

void USJ_InGameUserWidget::ClickQuit()
{
}
