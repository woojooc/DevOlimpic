// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_PingPongBallRepComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEVOLYMPIC_API USH_PingPongBallRepComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USH_PingPongBallRepComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 부모 액터 탁구공 받아오기
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
		class ASJ_PingPongBall* pingPongBall;


	// 이동 동기화 함수
	UPROPERTY()
	FTransform rep_ballTr;

	void UpdateTransform();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdateTr(FTransform _tr);
	bool Server_UpdateTr_Validate(FTransform _tr);
	void Server_UpdateTr_Implementation(FTransform _tr);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_UpdateTr(FTransform _tr);
	bool Multi_UpdateTr_Validate(FTransform _tr);
	void Multi_UpdateTr_Implementation(FTransform _tr);


	// 동기화할 값을 담을 변수들
	int32 rep_playerID;
	bool rep_inSideA;
	bool rep_inSideB;
	int rep_overlapA;
	int rep_overlapB;
	bool rep_isCallScoreGet;
	bool rep_canPingPongBallHit;

	// 업데이트 동기화 함수
	void  UpdateReplicate();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_UpdateReplicate
		(
			int32 _playerID,
			bool _inSideA,
			bool _inSideB,
			int _overlapA,
			int _overlapB,
			bool _isCallScoreGet,
			bool _canPingPongBallHit
		);
	bool Server_UpdateReplicate_Validate
	(
		int32 _playerID,
		bool _inSideA,
		bool _inSideB,
		int _overlapA,
		int _overlapB,
		bool _isCallScoreGet,
		bool _canPingPongBallHit
	);
	void Server_UpdateReplicate_Implementation
	(
		int32 _playerID,
		bool _inSideA,
		bool _inSideB,
		int _overlapA,
		int _overlapB,
		bool _isCallScoreGet,
		bool _canPingPongBallHit
	);

	// 서버에서 클라이언트를 움직일 함수
	// 서버의 컨트롤러 위치를 클라이언트들에게 전달
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_UpdateReplicate
		(
			int32 _playerID,
			bool _inSideA,
			bool _inSideB,
			int _overlapA,
			int _overlapB,
			bool _isCallScoreGet,
			bool _canPingPongBallHit
		);
	bool Multi_UpdateReplicate_Validate
	(
		int32 _playerID,
		bool _inSideA,
		bool _inSideB,
		int _overlapA,
		int _overlapB,
		bool _isCallScoreGet,
		bool _canPingPongBallHit
	);
	void Multi_UpdateReplicate_Implementation
	(
		int32 _playerID,
		bool _inSideA,
		bool _inSideB,
		int _overlapA,
		int _overlapB,
		bool _isCallScoreGet,
		bool _canPingPongBallHit
	);

};
