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

	// 탁구공 사운드
	UPROPERTY(EditAnywhere, Category = PingPongSound)
		class USoundBase* pingpongSound;

	// 점수 획득 사운드
	UPROPERTY(EditAnywhere, Category =PingPongSound)
	class USoundBase* scoreSound;

	// 탁구공이 탁구대에 맞았을때 생기는 이펙트
	UPROPERTY	(EditAnywhere, Category = HitPointEffect)
	class UParticleSystem* hitPointFX;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 어떤 플레이어가 쳤는지 검사, 서브 전에는 -1 따라서 랠리가 끝나고 다시 시작 할 때는 초기화
	UPROPERTY(VisibleAnywhere, Category = PlayerID)
		int32 playerID = -1;

	// Side A 에 맞았으면 true
	UPROPERTY(VisibleAnywhere, Category = SideID)
		bool inSideA;

	// Side B 에 맞았으면 true
	UPROPERTY(VisibleAnywhere, Category = SideID)
		bool inSideB;

	// OnCollisionGround가 불렸는지를 체크하는 Bool
	UPROPERTY(VisibleAnywhere, Category = BallState)
		bool isCallScoreGet = false;

	// hit 이벤트를 연산 가능한지 체크해주는 Bool
	UPROPERTY(VisibleAnywhere, Category = BallState)
		bool canPingPongBallHit = true;

	// Bool 초기화 함수
	void InitSideState();

	// 점수 득 실 났을 때 초기화 함수
	void ScoreGet(int id, bool scoreCheck);

	// 액터 파괴 함수
	void BallDestroy();

	// 파괴 타이머
	FTimerHandle destroyHandle;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		class UHapticFeedbackEffect_Base* hitFxHaptic;
};
