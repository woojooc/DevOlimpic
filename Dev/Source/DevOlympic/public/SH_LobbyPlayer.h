// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SH_LobbyPlayer.generated.h"

UCLASS()
class DEVOLYMPIC_API ASH_LobbyPlayer : public ACharacter
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
	class USH_HandActorComponent* handComp;

	// 로그 컴포넌트
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* rightLog;

	// 위젯 상호작용 포인터
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UWidgetInteractionComponent* widgetPointer;


	// 테스트용 이동 변수, 함수 선언
	// 이동 속도
	UPROPERTY(EditAnywhere, Category = MoveSettings)
	float moveSpeed = 200;
	// 이동함수
	void MoveHorizontal(float value);
	void MoveVertical(float value);

	// 변수 동기화를 위한 선언
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;


public:
	// 클라이언트에서 서버로 함수를 호출하기 위한 선언
	// 자신의 컨트롤러 위치를 서버에게 전달
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_HandMove(FTransform l_Trans, FTransform r_Trans);
	bool Server_HandMove_Validate(FTransform l_Trans, FTransform r_Trans);
	void Server_HandMove_Implementation(FTransform l_Trans, FTransform r_Trans);

	// 서버에서 클라이언트를 움직일 함수
	// 서버의 컨트롤러 위치를 클라이언트들에게 전달
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_HandMove(FTransform l_Trans, FTransform r_Trans);
	bool Multi_HandMove_Validate(FTransform l_Trans, FTransform r_Trans);
	void Multi_HandMove_Implementation(FTransform l_Trans, FTransform r_Trans);


	// 컨트롤러 위치 프로퍼티
	UPROPERTY()
		FTransform l_handRepTrans;
	UPROPERTY()
		FTransform r_handRepTrans;
};
