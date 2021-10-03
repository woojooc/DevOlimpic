// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_LobbyGameModeBase.h"
#include "WJ_LobbyMenu.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_AvatarObj.h"
#include "WJ_GameInstance.h"

AWJ_LobbyGameModeBase::AWJ_LobbyGameModeBase()
{

}

void AWJ_LobbyGameModeBase::BeginPlay()
{
	menuObj = Cast<AWJ_LobbyMenu>(UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_LobbyMenu::StaticClass()));
	CloseUI();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PlayPort", actors);
	if (actors.Num() > 0)
	{
		playPortObj = actors[0];
	}
	playPortObj->OnActorBeginOverlap.AddDynamic(this, &AWJ_LobbyGameModeBase::OnOverlap);
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
			gameInstance->avatarID = avatarObj->avatarID;
			bOpenedUI = true;
		}	
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
