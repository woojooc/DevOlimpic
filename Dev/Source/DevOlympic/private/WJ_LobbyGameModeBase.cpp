// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_LobbyGameModeBase.h"
#include "WJ_LobbyMenu.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_AvatarObj.h"
#include "WJ_GameInstance.h"
#include "WJ_TutorialObj.h"

AWJ_LobbyGameModeBase::AWJ_LobbyGameModeBase()
{

}

void AWJ_LobbyGameModeBase::BeginPlay()
{
	menuObj = Cast<AWJ_LobbyMenu>(UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_LobbyMenu::StaticClass()));
	CloseUI();

	// 경기장 입구 오브젝트 캐싱
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PlayPort", actors);
	if (actors.Num() > 0)
	{
		playPortObj = actors[0];
	}
	playPortObj->OnActorBeginOverlap.AddDynamic(this, &AWJ_LobbyGameModeBase::OnOverlap);

	// 아바타 오브젝트 캐싱
	TArray<AActor*> avatars;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_AvatarObj::StaticClass(), avatars);
	if (avatars.Num() > 0)
	{
		for (int i = 0; i < avatars.Num(); i++)
		{
			avatarObjs.Add(Cast<AWJ_AvatarObj>(avatars[i]));
		}
	}

	// 튜토리얼 UI 캐싱
	TArray<AActor*> tutoObj;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_TutorialObj::StaticClass(), tutoObj);
	if (tutoObj.Num() > 0)
	{
		for (int i = 0; i < tutoObj.Num(); i++)
		{
			auto tuto = Cast<AWJ_TutorialObj>(tutoObj[i]);
			if (tuto->tutoType == ETutoUIType::AvatarGrab)
			{
				avatarGrabUI.Add(tuto);
				tuto->SetOpen();
			}
			else if (tuto->tutoType == ETutoUIType::UIClick)
			{
				uiClickUI.Add(tuto);
				tuto->SetActorHiddenInGame(true);
			}
			else if (tuto->tutoType == ETutoUIType::Move)
			{
				thumbUI.Add(tuto);
				tuto->SetActorHiddenInGame(true);
			}
		}
	}
}

void AWJ_LobbyGameModeBase::InitGameState()
{

}

void AWJ_LobbyGameModeBase::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (bOpenedUI == false)
	{
		auto avatarObj = Cast<AWJ_AvatarObj>(OtherActor);
		if (avatarObj)
		{
			OpenUI();
			auto gameInstance = Cast<UWJ_GameInstance>(GetGameInstance());
			
			gameInstance->SetAvatarNum(avatarObj->avatarID);
			
			bOpenedUI = true;
			
			for (int i = 0; i < avatarObjs.Num(); i++)
			{
				avatarObjs[i]->HideText();
			}
			for (int i = 0; i < avatarGrabUI.Num(); i++)
			{	
				//avatarGrabUI[i]->SetActorHiddenInGame(true);
				avatarGrabUI[i]->SetClose();
			}
			for (int i = 0; i < uiClickUI.Num(); i++)
			{
				uiClickUI[i]->SetActorHiddenInGame(false);
				uiClickUI[i]->SetOpen();
			}
		}	
	}
}

void AWJ_LobbyGameModeBase::HideThumbTutoUI()
{
	for (int i = 0; i < thumbUI.Num(); i++)
	{
		//thumbUI[i]->SetActorHiddenInGame(true);
		thumbUI[i]->SetClose();
	}
}

void AWJ_LobbyGameModeBase::OpenUI()
{
	menuObj->SetActorHiddenInGame(false);
	menuObj->SetActorEnableCollision(true);
}

void AWJ_LobbyGameModeBase::CloseUI()
{
	menuObj->SetActorHiddenInGame(true);
	menuObj->SetActorEnableCollision(false);
}
