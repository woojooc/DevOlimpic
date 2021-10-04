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

	// 핑퐁 매니저 받아오기
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class AVRGameModeBase* vrGameModeBase;
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UWJ_PingPongMgr* pingPongManager;

	// 동기화할 값을 담을 변수들
	int rep_pointA;
	int rep_pointB;
	int rep_set;
	int rep_scoreA;
	int rep_scoreB;
	bool rep_bServPlayer;
	int rep_servCount;
	bool rep_bSpawnBall;
	bool rep_bIsDeuce;

	// 서브 상태 동기화 변수
	EPPBallState rep_p_State;


	// 매니저 동기화 함수
	void  UpdateReplicate();

	// 클라이언트에서 서버로 함수를 호출하기 위한 선언
	// 자신의 컨트롤러 위치를 서버에게 전달
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
			EPPBallState _p_State
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
		EPPBallState _p_State
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
		EPPBallState _p_State
	);

	// 서버에서 클라이언트를 움직일 함수
	// 서버의 컨트롤러 위치를 클라이언트들에게 전달
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
		EPPBallState _p_State
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
		EPPBallState _p_State
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
		EPPBallState _p_State
	);
};
