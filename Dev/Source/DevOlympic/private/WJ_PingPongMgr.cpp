// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_PingPongMgr.h"

// Sets default values for this component's properties
UWJ_PingPongMgr::UWJ_PingPongMgr()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWJ_PingPongMgr::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWJ_PingPongMgr::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (m_state)
	{
	case EPingPongState::Intro:
		// 대기
		Intro();
		break;

	case EPingPongState::Serv:
		// 공 소환
		Serv();
		break;

	case EPingPongState::Rally:
		// 충돌 체크
		Rally();
		break;

	case EPingPongState::RallyOver:
		// 공 제거
		// 점수(point) 획득
		// 10 : 10 ==> Serv, bIsDeuse = true : 2점차날때까지 반복
		// point < 11 ==> Serv
		// 11 ==> SetOver
		RallyOver();
		break;

	case EPingPongState::SetOver:
		// set < 5  ==>  Serv
		// 5 ==> MatchOver
		SetOver();
		break;

	case EPingPongState::MatchOver:
		// score 비교 승자 결정
		MatchOver();
		break;

	default:
		break;
	}
}

void UWJ_PingPongMgr::Intro()
{

}

void UWJ_PingPongMgr::Serv()
{
	// 공이 스폰되었으면 대기
	if (bSpawnBall)
	{
		return;
	}

	// bServPlayer가 T -> A 위치에 공 스폰
	// else -> B 위치에 공 스폰
	if (bServPlayer)
	{
		//A 공 스폰
	}
	else
	{
		//B 공 스폰
	}

	// 플레이어가 공을 치면 이벤트 발생
}

void UWJ_PingPongMgr::Rally()
{
	
}

void UWJ_PingPongMgr::RallyOver()
{

}

void UWJ_PingPongMgr::SetOver()
{

}

void UWJ_PingPongMgr::MatchOver()
{

}

void UWJ_PingPongMgr::SetState(EPingPongState state)
{
	m_state = state;
}

EPingPongState UWJ_PingPongMgr::GetState()
{
	return m_state;
}

void UWJ_PingPongMgr::StartRally()
{
	SetState(EPingPongState::Rally);
}

void UWJ_PingPongMgr::OnCollisionGround(int player, bool in)
{
	if (in)
	{
		// player point ++
		// if Deuce point ++
	}
	else
	{
		// other player point ++
		// if Deuce point ++
	}

	// 듀스 2점차 이상 세트 종료
	if (bIsDeuce)
	{
		if (pointA - pointB >= 2 || pointA - pointB <= -2)
		{
			// 스코어 계산
			SetState(EPingPongState::SetOver);
			return;
		}
	}
	else 
	{
		// 듀스 아닌 경우 11점 획득시 세트 종료
		if (pointA == 11 || pointB == 11)
		{
			// 스코어 계산
			SetState(EPingPongState::SetOver);
			return;
		}
	}

	if (pointA == 10 && pointB == 10)
	{
		bIsDeuce = true;
	}

	SetState(EPingPongState::Serv);
}