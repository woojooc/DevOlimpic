// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SJ_PingPongPlayer.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_PingPongPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASJ_PingPongPlayer();

	// 플레이어 콜라이더
	UPROPERTY(EditAnywhere, Category = Player)
		class UCapsuleComponent* capsuleComp;

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

	// 레이저
	UPROPERTY(EditAnywhere, Category = Player)
	class UChildActorComponent* razer;

	UPROPERTY(EditAnywhere, Category = Player)
	class USJ_SelectUIComponent* selectComp;

	UPROPERTY(EditAnywhere, Category = Player)
	class USH_PlayerReplicateComponent* playerRepComp;

	// 위젯 상호작용 포인터
	UPROPERTY(EditAnywhere, Category = WidgetInteraction)
	class UWidgetInteractionComponent* widgetPointer;

	// 게임 모드
	UPROPERTY(EditAnywhere, Category = GameMode)
	class AVRGameModeBase* gameMode;

	UPROPERTY(EditAnywhere, Category = UI)
	TArray<class AWJ_GameOverUI*> gameOverUI;

	UPROPERTY(EditAnywhere, Category = Material)
	class UMaterial* marioFace;
		
	UPROPERTY(EditAnywhere, Category = Material)
	class UMaterial* marioBody;

	UPROPERTY(EditAnywhere, Category = Material)
	class UMaterial* luigiFace;

	UPROPERTY(EditAnywhere, Category = Material)
	class UMaterial* luigiBody;

	// 캡텨 카메라
	UPROPERTY(EditAnywhere, Category = CaptureCamera)
		class USceneCaptureComponent2D* captureCamera;

	UPROPERTY()
	TArray<class UTextureRenderTarget2D*> renderTexture;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 호스트와 클라이언트를 구분해주는 번호(Host = 0, Client = 1)
	UPROPERTY(VisibleAnywhere, Category = PlayerSetting)
	int playerIndex;

	// 초기화 타이머
	FTimerHandle resetHandle;

	// 초기화 함수
	void ResetHMD();

	void ShowUI();

	// 입장시 위치 초기화 변수
	FRotator hmdRotation;
	FVector hmdLocation;

	// HMD 회전값을 플레이어 머리에 전달하는 변수
	FRotator headRotation;
	FVector headLocation;
};
