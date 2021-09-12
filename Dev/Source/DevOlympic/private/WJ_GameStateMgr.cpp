// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_GameStateMgr.h"

// Sets default values for this component's properties
UWJ_GameStateMgr::UWJ_GameStateMgr()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWJ_GameStateMgr::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWJ_GameStateMgr::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWJ_GameStateMgr::SetState(EGameState state)
{
	m_state = state;

	switch (m_state)
	{
	case EGameState::Lobby:
		break;
	case EGameState::PingPong:

		break;
	case EGameState::GameOver:
		break;
	default:
		break;
	}
}

EGameState UWJ_GameStateMgr::GetState()
{
	return m_state;
}