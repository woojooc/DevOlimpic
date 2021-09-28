// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SH_LobbyPlayer.generated.h"

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
	class USH_HandActorComponent* handComp;

	// 로그 컴포넌트
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* rightLog;

	// 위젯 상호작용 포인터
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UWidgetInteractionComponent* widgetPointer;

	// 캐릭터 무브먼트 컴포넌트(동기화용)
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UCharacterMovementComponent* characterMoveComp;



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
	void Server_HandMove(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	bool Server_HandMove_Validate(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	void Server_HandMove_Implementation(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);

	// 서버에서 클라이언트를 움직일 함수
	// 서버의 컨트롤러 위치를 클라이언트들에게 전달
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_HandMove(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	bool Multi_HandMove_Validate(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	void Multi_HandMove_Implementation(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);


	// 컨트롤러 위치 프로퍼티
	UPROPERTY()
	FVector l_handRepLoc;
	UPROPERTY()
	FRotator l_handRepRot;
	UPROPERTY()
	FVector r_handRepLoc;
	UPROPERTY()
	FRotator r_handRepRot;


	//// 손 위치 변수를 동기화
	//// 왼손 위치 동기화 변수
	//UPROPERTY(Replicated)
	//	FTransform l_handRepTrans;

	//// 오른손 위치 동기화 변수
	//UPROPERTY(Replicated)
	//	FTransform r_handRepTrans;


	//// 컨트롤러 위치 프로퍼티
	//UPROPERTY(Replicated)
	//	FVector l_handRepLoc;
	//UPROPERTY(Replicated)
	//	FRotator l_handRepRot;

	//UPROPERTY(Replicated)
	//	FVector r_handRepLoc;
	//UPROPERTY(Replicated)
	//	FRotator r_handRepRot;
};
