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


	// �� ��ġ ������ ����ȭ
	// RPC �Լ� : ������ ���� ����ġ�� �ű⵵�� �Ѵ�(���� ����)
	// ���� ��ġ�� ���� �Űܶ�
	// ���� : ��Ƽĳ��Ʈ
	// Ŭ���̾�Ʈ : ������ ����, �������� ��Ƽĳ��Ʈ�� ����
	 
	// ���� ����ȭ�� ���� ����
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;


	// �� ��ġ ������ ����ȭ
	// �޼� ��ġ ����ȭ ����
	UPROPERTY(Replicated)
	FTransform l_handRepTrans;

	// ������ ��ġ ����ȭ ����
	UPROPERTY(Replicated)
	FTransform r_handRepTrans;

	// RPC �Լ� : ������ ���� ����ġ�� �ű⵵�� �Ѵ�(���� ����)
	//UFUNCTION(Server, Reliable, WithValidation)
	//void Server_SyncHand(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot );
	//bool Server_SyncHand_Validate(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot)
	//void Server_SyncHand_Implementation(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);

	//// shotFired������ ����ɶ����� ȣ��Ǵ� �Լ�
	//UFUNCTION(NetMulticast, Reliable, WithValidation)
	//void Multi_SyncHand(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);
	//bool Multi_SyncHand_Validate(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);
	//void Multi_SyncHand_Implementation(FVector l_handRepPos, FRotator l_handRepRot, FVector r_handRepPos, FRotator r_handRepRot);

};
