// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SH_RoomPlayer.generated.h"

UCLASS()
class DEVOLYMPIC_API ASH_RoomPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASH_RoomPlayer();

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


	// 손 위치 변수를 동기화
	// RPC 함수 : 변수에 따라 손위치를 옮기도록 한다(로컬 제외)
	// 변수 위치로 손을 옮겨라
	// 서버 : 멀티캐스트
	// 클라이언트 : 서버에 전달, 서버에서 멀티캐스트로 전달
	 
	// 변수 동기화를 위한 선언
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;


	// 손 위치 변수를 동기화
	// 왼손 위치 동기화 변수
	UPROPERTY(Replicated)
	FTransform l_handRepTrans;

	// 오른손 위치 동기화 변수
	UPROPERTY(Replicated)
	FTransform r_handRepTrans;

	// RPC 함수 : 변수에 따라 손위치를 옮기도록 한다(로컬 제외)
	//UFUNCTION(Server, Reliable, WithValidation)
	//void Server_SyncHand(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot );
	//bool Server_SyncHand_Validate(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot)
	//void Server_SyncHand_Implementation(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);

	//// shotFired변수가 변경될때마다 호출되는 함수
	//UFUNCTION(NetMulticast, Reliable, WithValidation)
	//void Multi_SyncHand(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);
	//bool Multi_SyncHand_Validate(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);
	//void Multi_SyncHand_Implementation(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);

};
