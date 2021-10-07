// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ModeSelectUserWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "WJ_GameInstance.h"


void UWJ_ModeSelectUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Single->OnClicked.AddDynamic(this, &UWJ_ModeSelectUserWidget::ClickSingle);
	Btn_Multi->OnClicked.AddDynamic(this, &UWJ_ModeSelectUserWidget::ClickMulti);
}

void UWJ_ModeSelectUserWidget::ClickSingle()
{
	auto gameInstance = Cast<UWJ_GameInstance>(GetGameInstance());
	gameInstance->SetModeNum(EEditMode::Single);

	// Level ¿ÀÇÂ
	UGameplayStatics::OpenLevel(GetWorld(),"SingleModeMap");
}

void UWJ_ModeSelectUserWidget::ClickMulti()
{
	auto gameInstance = Cast<UWJ_GameInstance>(GetGameInstance());
	gameInstance->SetModeNum(EEditMode::Multi);

	//UE_LOG(LogTemp, Warning, TEXT("gameInstance : %d"), gameInstance->modeNum);
}
