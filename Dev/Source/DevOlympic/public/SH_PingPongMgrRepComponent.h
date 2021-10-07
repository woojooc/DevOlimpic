// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DevOlympic.h"
#include "Components/ActorComponent.h"
#include "SH_PingPongMgrRepComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API USH_PingPongMgrRepComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USH_PingPongMgrRepComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ���� �Ŵ��� �޾ƿ���
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class AVRGameModeBase* vrGameModeBase;
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UWJ_PingPongMgr* pingPongManager;

	// ����ȭ�� ���� ���� ������
	int rep_pointA;
	int rep_pointB;
	int rep_set;
	int rep_scoreA;
	int rep_scoreB;
	bool rep_bServPlayer;
	int rep_servCount;
	bool rep_bSpawnBall;
	bool rep_bIsDeuce;

	// ���� ���� ����ȭ ����
	EPPBallState rep_p_State;
	EPingPongState rep_m_state;

	// Ź�� ���� ���� ���� ����ȭ ����
	bool rep_isGameStarted;

	// �Ŵ��� ����ȭ �Լ�
	void  UpdateReplicate();

	// Ŭ���̾�Ʈ���� ������ �Լ��� ȣ���ϱ� ���� ����
	// �ڽ��� ��Ʈ�ѷ� ��ġ�� �������� ����
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_UpdateReplicate
		(
			int _pointA,
			int _pointB,
			int _set,
			int _scoreA,
			int _scoreB,
			bool _bServPlayer,
			int _servCount,
			bool _bSpawnBall,
			bool _bIsDeuce,
			EPPBallState _p_State,
			bool _isGameStarted,
			EPingPongState _m_state

	);
	bool Server_UpdateReplicate_Validate
	(
		int _pointA,
		int _pointB,
		int _set,
		int _scoreA,
		int _scoreB,
		bool _bServPlayer,
		int _servCount,
		bool _bSpawnBall,
		bool _bIsDeuce,
		EPPBallState _p_State,
		bool _isGameStarted,
		EPingPongState _m_state
	);
	void Server_UpdateReplicate_Implementation
	(
		int _pointA,
		int _pointB,
		int _set,
		int _scoreA,
		int _scoreB,
		bool _bServPlayer,
		int _servCount,
		bool _bSpawnBall,
		bool _bIsDeuce,
		EPPBallState _p_State,
		bool _isGameStarted,
		EPingPongState _m_state
	);

	// �������� Ŭ���̾�Ʈ�� ������ �Լ�
	// ������ ��Ʈ�ѷ� ��ġ�� Ŭ���̾�Ʈ�鿡�� ����
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_UpdateReplicate
	(
		int _pointA,
		int _pointB,
		int _set,
		int _scoreA,
		int _scoreB,
		bool _bServPlayer,
		int _servCount,
		bool _bSpawnBall,
		bool _bIsDeuce,
		EPPBallState _p_State,
		bool _isGameStarted,
		EPingPongState _m_state
	);
	bool Multi_UpdateReplicate_Validate
	(
		int _pointA,
		int _pointB,
		int _set,
		int _scoreA,
		int _scoreB,
		bool _bServPlayer,
		int _servCount,
		bool _bSpawnBall,
		bool _bIsDeuce,
		EPPBallState _p_State,
		bool _isGameStarted,
		EPingPongState _m_state
	);
	void Multi_UpdateReplicate_Implementation
	(
		int _pointA,
		int _pointB,
		int _set,
		int _scoreA,
		int _scoreB,
		bool _bServPlayer,
		int _servCount,
		bool _bSpawnBall,
		bool _bIsDeuce,
		EPPBallState _p_State,
		bool _isGameStarted,
		EPingPongState _m_state
	);
};
