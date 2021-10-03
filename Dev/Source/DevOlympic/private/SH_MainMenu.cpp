// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_MainMenu.h"
#include <Components/Button.h>

void USH_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Host->OnClicked.AddDynamic(this, &USH_MainMenu::HostGame);
	btn_Join->OnClicked.AddDynamic(this, &USH_MainMenu::JoinGame);
	//btn_Quit->OnClicked.AddDynamic(this, &USH_MainMenu::QuitGame);

}

//void USH_MainMenu::HostGame()
//{
//
//}
//
//void USH_MainMenu::JoinGame()
//{
//
//}
//
//void USH_MainMenu::QuitGame()
//{
//	// 게임을 종료
//	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
//}
