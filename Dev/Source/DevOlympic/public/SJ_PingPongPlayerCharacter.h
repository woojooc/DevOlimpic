// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SJ_PingPongPlayerCharacter.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_PingPongPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASJ_PingPongPlayerCharacter();

	// 카메라, 컨트롤러 담는 뿌리 컴포넌트
	UPROPERTY(EditAnywhere, Category = Player)
		class USceneComponent* cameraRoot;

	// 플레이어 카메라
	UPROPERTY(EditAnywhere, Category = Player)
		class UCameraComponent* playerCam;

	// 플레이어 얼굴
	UPROPERTY(EditAnywhere, Category = Player)
		class UStaticMeshComponent* playerFace;

	// 플레이어 몸통
	UPROPERTY(EditAnywhere, Category = Player)
		class UStaticMeshComponent* playerBody;

	// 플레이어 왼손 컨트롤러
	UPROPERTY(EditAnywhere, Category = Player)
		class UMotionControllerComponent* leftController;

	// 플레이어 왼손 모델(기본제공 손모델 사용)
	UPROPERTY(EditAnywhere, Category = Player)
		class USkeletalMeshComponent* leftHand;

	// 플레이어 오른손 컨트롤러
	UPROPERTY(EditAnywhere, Category = Player)
		class UMotionControllerComponent* rightController;

	// 플레이어 오른손 모델
	UPROPERTY(EditAnywhere, Category = Player)
		class USkeletalMeshComponent* rightHand;

	// 플레이어 오른손 모델(라켓)
	UPROPERTY(EditAnywhere, Category = Player)
		class UStaticMeshComponent* racket;

	// 라켓 차일드화
	UPROPERTY(EditAnywhere, Category = Player)
		class UChildActorComponent* childRacket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 호스트와 클라이언트를 구분해주는 번호(Host = 0, Client = 1)
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		int playerIndex;

	// 초기화 타이머
	FTimerHandle resetHandle;

	// 초기화 함수
	void ResetHMD();

	// 초기화 변수
	FRotator hmdRotation;
	FVector hmdLocation;

	// 플레이어 머리 회전값
	FRotator headRotation;
	FVector headLocation;

};
