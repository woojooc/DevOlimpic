// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SH_LobbyPlayer.generated.h"


// 2인이 대기 방에 접속
// 스팀으로 연결
// 방을 생성
// 방에 입장
// 대기 버튼 누르기
// 두 플레이어가 모두 대기버튼을 누르면 게임 레벨로 넘어간다(이후 동기화 등으로 게임 진행)

// 스팀(혹은 데디케이티드 서버)로 연결, VR 플레이어가 한방에 있을 수 있도록 테스트
// 대기방 만들기 대기 버튼을 누르면 게임 레벨에 입장
// UI 작업
// 오브젝트를 집어서 두면 네트워크 / 싱글 플레이 버튼이 나오게끔 설정
// 오브젝트 잡기, 배치하기, UI 작업

UCLASS()
class DEVOLYMPIC_API ASH_LobbyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASH_LobbyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCapsuleComponent* capsuleComp;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* cameraRoot;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCameraComponent* playerCam;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	class USH_HandActorComponent* handComp;
};
