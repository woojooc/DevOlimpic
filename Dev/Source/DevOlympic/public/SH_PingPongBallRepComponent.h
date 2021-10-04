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

	// �θ� ���� Ź���� �޾ƿ���
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
		class ASJ_PingPongBall* pingPongBall;


	// �̵� ����ȭ �Լ�
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


	// ����ȭ�� ���� ���� ������
	int32 rep_playerID;
	bool rep_inSideA;
	bool rep_inSideB;
	int rep_overlapA;
	int rep_overlapB;
	bool rep_isCallScoreGet;
	bool rep_canPingPongBallHit;

	// ������Ʈ ����ȭ �Լ�
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

	// �������� Ŭ���̾�Ʈ�� ������ �Լ�
	// ������ ��Ʈ�ѷ� ��ġ�� Ŭ���̾�Ʈ�鿡�� ����
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
