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
		// ���
		Intro();
		break;

	case EPingPongState::Serv:
		// �� ��ȯ
		Serv();
		break;

	case EPingPongState::Rally:
		// �浹 üũ
		Rally();
		break;

	case EPingPongState::RallyOver:
		// �� ����
		// ����(point) ȹ��
		// 10 : 10 ==> Serv, bIsDeuse = true : 2������������ �ݺ�
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
		// score �� ���� ����
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
	// ���� �����Ǿ����� ���
	if (bSpawnBall)
	{
		return;
	}

	// bServPlayer�� T -> A ��ġ�� �� ����
	// else -> B ��ġ�� �� ����
	if (bServPlayer)
	{
		//A �� ����
	}
	else
	{
		//B �� ����
	}

	// �÷��̾ ���� ġ�� �̺�Ʈ �߻�
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

	// �ེ 2���� �̻� ��Ʈ ����
	if (bIsDeuce)
	{
		if (pointA - pointB >= 2 || pointA - pointB <= -2)
		{
			// ���ھ� ���
			SetState(EPingPongState::SetOver);
			return;
		}
	}
	else 
	{
		// �ེ �ƴ� ��� 11�� ȹ��� ��Ʈ ����
		if (pointA == 11 || pointB == 11)
		{
			// ���ھ� ���
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