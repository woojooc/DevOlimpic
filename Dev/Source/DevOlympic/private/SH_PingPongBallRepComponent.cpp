// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_PingPongBallRepComponent.h"
#include "SJ_PingPongBall.h"

// Sets default values for this component's properties
USH_PingPongBallRepComponent::USH_PingPongBallRepComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USH_PingPongBallRepComponent::BeginPlay()
{
	Super::BeginPlay();

	pingPongBall = Cast<ASJ_PingPongBall>(GetOwner());
}


// Called every frame
void USH_PingPongBallRepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���� ����ȭ
	UpdateReplicate();
	// Ʈ������ ��ġ ����ȭ
	UpdateTransform();
}

void USH_PingPongBallRepComponent::UpdateTransform()
{
	// �������
	if (pingPongBall->HasAuthority())
	{
		Multi_UpdateTr_Implementation(pingPongBall->GetActorTransform());
	}
}

bool USH_PingPongBallRepComponent::Server_UpdateTr_Validate(FTransform _tr)
{
	return true;
}

void USH_PingPongBallRepComponent::Server_UpdateTr_Implementation(FTransform _tr)
{
	Multi_UpdateTr_Implementation(_tr);
}

bool USH_PingPongBallRepComponent::Multi_UpdateTr_Validate(FTransform _tr)
{
	return true;
}

void USH_PingPongBallRepComponent::Multi_UpdateTr_Implementation(FTransform _tr)
{
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!pingPongBall)
	{
		pingPongBall = Cast<ASJ_PingPongBall>(GetOwner());
	}

	pingPongBall->SetActorTransform(_tr);
}

void USH_PingPongBallRepComponent::UpdateReplicate()
{
	// ���� Ź���� ���� �Է�
	rep_playerID = pingPongBall->playerID;
	rep_inSideA = pingPongBall->inSideA;
	rep_inSideB = pingPongBall->inSideB;
	rep_overlapA = pingPongBall->overlapA;
	rep_overlapB = pingPongBall->overlapB;
	rep_isCallScoreGet = pingPongBall->isCallScoreGet;
	rep_canPingPongBallHit = pingPongBall->canPingPongBallHit;

	// ������ �ƴ϶��
	if (!pingPongBall->HasAuthority())
	{
		// ���� �Լ� ����
		Server_UpdateReplicate(rep_playerID, rep_inSideA, rep_inSideB, rep_overlapA, rep_overlapB, rep_isCallScoreGet, rep_canPingPongBallHit);
	}
	// �������
	else
	{
		// ��ٷ� ��Ƽĳ��Ʈ �Լ� ����
		Multi_UpdateReplicate(rep_playerID, rep_inSideA, rep_inSideB, rep_overlapA, rep_overlapB, rep_isCallScoreGet, rep_canPingPongBallHit);
	}
}

bool USH_PingPongBallRepComponent::Server_UpdateReplicate_Validate( int32 _playerID, bool _inSideA, bool _inSideB, int _overlapA, int _overlapB, bool _isCallScoreGet, bool _canPingPongBallHit)
{
	return true;
}

void USH_PingPongBallRepComponent::Server_UpdateReplicate_Implementation( int32 _playerID, bool _inSideA, bool _inSideB, int _overlapA, int _overlapB, bool _isCallScoreGet, bool _canPingPongBallHit)
{
	Multi_UpdateReplicate_Implementation(_playerID,  _inSideA,  _inSideB,  _overlapA,  _overlapB,  _isCallScoreGet,  _canPingPongBallHit);
}

bool USH_PingPongBallRepComponent::Multi_UpdateReplicate_Validate( int32 _playerID, bool _inSideA, bool _inSideB, int _overlapA, int _overlapB, bool _isCallScoreGet, bool _canPingPongBallHit)
{
	return true;
}

void USH_PingPongBallRepComponent::Multi_UpdateReplicate_Implementation( int32 _playerID, bool _inSideA, bool _inSideB, int _overlapA, int _overlapB, bool _isCallScoreGet, bool _canPingPongBallHit)
{
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!pingPongBall)
	{
		pingPongBall = Cast<ASJ_PingPongBall>(GetOwner());
	}

	// �޾ƿ� Ź���� ���� �����ϱ�
	pingPongBall->playerID = _playerID;
	pingPongBall->inSideA = _inSideA;
	pingPongBall->inSideB = _inSideB;
	pingPongBall->overlapA = _overlapA;
	pingPongBall->overlapB = _overlapB;
	pingPongBall->isCallScoreGet = _isCallScoreGet;
	pingPongBall->canPingPongBallHit = _canPingPongBallHit;
}

