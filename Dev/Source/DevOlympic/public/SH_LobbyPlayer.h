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

	// �α� ������Ʈ
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* rightLog;

	// ���� ��ȣ�ۿ� ������
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UWidgetInteractionComponent* widgetPointer;

	// ĳ���� �����Ʈ ������Ʈ(����ȭ��)
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UCharacterMovementComponent* characterMoveComp;



	// �׽�Ʈ�� �̵� ����, �Լ� ����
	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = MoveSettings)
	float moveSpeed = 200;
	// �̵��Լ�
	void MoveHorizontal(float value);
	void MoveVertical(float value);

	// ���� ����ȭ�� ���� ����
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;


public:
	// Ŭ���̾�Ʈ���� ������ �Լ��� ȣ���ϱ� ���� ����
	// �ڽ��� ��Ʈ�ѷ� ��ġ�� �������� ����
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_HandMove(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	bool Server_HandMove_Validate(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	void Server_HandMove_Implementation(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);

	// �������� Ŭ���̾�Ʈ�� ������ �Լ�
	// ������ ��Ʈ�ѷ� ��ġ�� Ŭ���̾�Ʈ�鿡�� ����
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_HandMove(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	bool Multi_HandMove_Validate(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);
	void Multi_HandMove_Implementation(FVector l_loc, FRotator l_rot, FVector r_loc, FRotator r_rot);


	// ��Ʈ�ѷ� ��ġ ������Ƽ
	UPROPERTY()
	FVector l_handRepLoc;
	UPROPERTY()
	FRotator l_handRepRot;
	UPROPERTY()
	FVector r_handRepLoc;
	UPROPERTY()
	FRotator r_handRepRot;


	//// �� ��ġ ������ ����ȭ
	//// �޼� ��ġ ����ȭ ����
	//UPROPERTY(Replicated)
	//	FTransform l_handRepTrans;

	//// ������ ��ġ ����ȭ ����
	//UPROPERTY(Replicated)
	//	FTransform r_handRepTrans;


	//// ��Ʈ�ѷ� ��ġ ������Ƽ
	//UPROPERTY(Replicated)
	//	FVector l_handRepLoc;
	//UPROPERTY(Replicated)
	//	FRotator l_handRepRot;

	//UPROPERTY(Replicated)
	//	FVector r_handRepLoc;
	//UPROPERTY(Replicated)
	//	FRotator r_handRepRot;
};
