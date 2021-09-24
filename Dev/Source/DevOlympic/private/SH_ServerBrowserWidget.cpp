// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_ServerBrowserWidget.h"
#include <Components/Button.h>

void USH_ServerBrowserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Join->OnClicked.AddDynamic(this, &USH_ServerBrowserWidget::JoinGame);
	btn_Refresh->OnClicked.AddDynamic(this, &USH_ServerBrowserWidget::RefreshServerList);
	btn_Back->OnClicked.AddDynamic(this, &USH_ServerBrowserWidget::BackToMainMenu);
}