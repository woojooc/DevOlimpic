// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_PingPongMgrRepComponent.h"
// vr ���� ��� ���̽� ��� �߰�
#include "VRGameModeBase.h"
// ���� �Ŵ��� ������Ʈ �߰�
#include "WJ_PingPongMgr.h"
// �𸮾� ��Ʈ��ũ ��� �߰�
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USH_PingPongMgrRepComponent::USH_PingPongMgrRepComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USH_PingPongMgrRepComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	vrGameModeBase = Cast<AVRGameModeBase>(GetOwner());
	if(vrGameModeBase)
	pingPongManager = vrGameModeBase->pingpongStateMgr;
}


// Called every frame
void USH_PingPongMgrRepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ������Ʈ���� ���� ����ȭ
	UpdateReplicate();
}


void USH_PingPongMgrRepComponent::UpdateReplicate()
{
	// ���� �Ŵ��� ���� �޾ƿ���
	FPingPongData temp = pingPongManager->GetFPPData();

	rep_pointA = temp.pointA;
	rep_pointB = temp.pointB;
	rep_set = temp.set;
	rep_scoreA = temp.scoreA;
	rep_scoreB = temp.scoreB;
	rep_bServPlayer = temp.bServPlayer;
	rep_servCount = temp.servCount;
	rep_bSpawnBall = temp.bSpawnBall;
	rep_bIsDeuce = temp.bIsDeuce;

	rep_p_State = pingPongManager->p_State;

	// ������ �ƴ϶��
	if (!vrGameModeBase->HasAuthority())
	{
		// ���� �Լ� ����
		Server_UpdateReplicate(rep_pointA, rep_pointB, rep_set, rep_scoreA, rep_scoreB, rep_bServPlayer, rep_servCount, rep_bSpawnBall, rep_bIsDeuce, rep_p_State);
	}
	// �������
	else
	{
		// ��ٷ� ��Ƽĳ��Ʈ �Լ� ����
		Multi_UpdateReplicate(rep_pointA, rep_pointB, rep_set, rep_scoreA, rep_scoreB, rep_bServPlayer, rep_servCount, rep_bSpawnBall, rep_bIsDeuce, rep_p_State);
	}
}

bool USH_PingPongMgrRepComponent::Server_UpdateReplicate_Validate(int _pointA, int _pointB, int _set, int _scoreA, int _scoreB, bool _bServPlayer, int _servCount, bool _bSpawnBall, bool _bIsDeuce, EPPBallState _p_State)
{
	return true;
}

void USH_PingPongMgrRepComponent::Server_UpdateReplicate_Implementation(int _pointA, int _pointB, int _set, int _scoreA, int _scoreB, bool _bServPlayer, int _servCount, bool _bSpawnBall, bool _bIsDeuce, EPPBallState _p_State)
{
	Multi_UpdateReplicate_Implementation(_pointA, _pointB, _set, _scoreA, _scoreB, _bServPlayer, _servCount, _bSpawnBall, _bIsDeuce, rep_p_State);
}

bool USH_PingPongMgrRepComponent::Multi_UpdateReplicate_Validate(int _pointA, int _pointB, int _set, int _scoreA, int _scoreB, bool _bServPlayer, int _servCount, bool _bSpawnBall, bool _bIsDeuce, EPPBallState _p_State)
{
	return true;
}

void USH_PingPongMgrRepComponent::Multi_UpdateReplicate_Implementation(int _pointA, int _pointB, int _set, int _scoreA, int _scoreB, bool _bServPlayer, int _servCount, bool _bSpawnBall, bool _bIsDeuce, EPPBallState _p_State)
{
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!pingPongManager)
	{
		vrGameModeBase = Cast<AVRGameModeBase>(GetOwner());
		pingPongManager = vrGameModeBase->pingpongStateMgr;
	}

	FPingPongData temp;
	temp.pointA = _pointA;
	temp.pointB = _pointB;
	temp.set = _set;
	temp.scoreA = _scoreA;
	temp.scoreB = _scoreB;
	temp.bServPlayer = _bServPlayer;
	temp.servCount = _servCount;
	temp.bSpawnBall = _bSpawnBall;
	temp.bIsDeuce = _bIsDeuce;


	// ���Ӱ� �Ҵ�� �� �Ŵ����� ����
	pingPongManager->SetFPPData(temp);
	// ���� ���� �� �Ŵ����� ����
	pingPongManager->p_State = _p_State;
}

