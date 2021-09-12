// Fill out your copyright notice in the Description page of Project Settings.


#include "VRGameModeBase.h"
#include "WJ_GameStateMgr.h"
#include "WJ_PingPongMgr.h"

AVRGameModeBase::AVRGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// #Component »ý¼º
	gameStateMgr = CreateDefaultSubobject<UWJ_GameStateMgr>(TEXT("GameStateManager"));
	pingpongStateMgr = CreateDefaultSubobject<UWJ_PingPongMgr>(TEXT("PingPongStateManager"));
}

void AVRGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVRGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void AVRGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}