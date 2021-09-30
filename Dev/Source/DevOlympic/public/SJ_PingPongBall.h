// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DevOlympic.h"
#include "GameFramework/Actor.h"
#include "SJ_PingPongBall.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_PingPongBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASJ_PingPongBall();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongBall)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = PingPongBall)
		class UStaticMeshComponent* wrapFX;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Ź���� ����
	UPROPERTY(EditAnywhere, Category = PingPongSound)
		class USoundBase* pingpongSound;

	// ���� ȹ�� ����
	UPROPERTY(EditAnywhere, Category =PingPongSound)
	class USoundBase* scoreSound;

	// Ź������ Ź���뿡 �¾����� ����� ����Ʈ
	UPROPERTY	(EditAnywhere, Category = HitPointEffect)
	class UParticleSystem* hitPointFX;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// � �÷��̾ �ƴ��� �˻�, ���� ������ -1 ���� ������ ������ �ٽ� ���� �� ���� �ʱ�ȭ
	UPROPERTY(VisibleAnywhere, Category = PlayerID)
		int32 playerID = -1;

	// Side A �� �¾����� true
	UPROPERTY(VisibleAnywhere, Category = SideID)
		bool inSideA;

	// Side B �� �¾����� true
	UPROPERTY(VisibleAnywhere, Category = SideID)
		bool inSideB;

	// OnCollisionGround�� �ҷȴ����� üũ�ϴ� Bool
	UPROPERTY(VisibleAnywhere, Category = BallState)
		bool isCallScoreGet = false;

	// hit �̺�Ʈ�� ���� �������� üũ���ִ� Bool
	UPROPERTY(VisibleAnywhere, Category = BallState)
		bool canPingPongBallHit = true;

	// Bool �ʱ�ȭ �Լ�
	void InitSideState();

	// ���� �� �� ���� �� �ʱ�ȭ �Լ�
	void ScoreGet(int id, bool scoreCheck);

	// ���� �ı� �Լ�
	void BallDestroy();

	// �ı� Ÿ�̸�
	FTimerHandle destroyHandle;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		class UHapticFeedbackEffect_Base* hitFxHaptic;
};
