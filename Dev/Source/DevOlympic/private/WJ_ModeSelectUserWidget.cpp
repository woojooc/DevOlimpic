// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ModeSelectUserWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>


void UWJ_ModeSelectUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Single->OnClicked.AddDynamic(this, &UWJ_ModeSelectUserWidget::ClickSingle);
	//Btn_Multi->OnClicked.AddDynamic(this, &UWJ_ModeSelectUserWidget::ClickMulti);
}

void UWJ_ModeSelectUserWidget::ClickSingle()
{
	// Level ¿ÀÇÂ
	UGameplayStatics::OpenLevel(GetWorld(),"WJPPMap");
}

void UWJ_ModeSelectUserWidget::ClickMulti()
{
	
}
