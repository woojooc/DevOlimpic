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

	// �α� ������Ʈ
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* rightLog;

	// ���� ��ȣ�ۿ� ������
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UWidgetInteractionComponent* widgetPointer;


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
	void Server_HandMove(FTransform l_Trans, FTransform r_Trans);
	bool Server_HandMove_Validate(FTransform l_Trans, FTransform r_Trans);
	void Server_HandMove_Implementation(FTransform l_Trans, FTransform r_Trans);

	// �������� Ŭ���̾�Ʈ�� ������ �Լ�
	// ������ ��Ʈ�ѷ� ��ġ�� Ŭ���̾�Ʈ�鿡�� ����
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_HandMove(FTransform l_Trans, FTransform r_Trans);
	bool Multi_HandMove_Validate(FTransform l_Trans, FTransform r_Trans);
	void Multi_HandMove_Implementation(FTransform l_Trans, FTransform r_Trans);


	// ��Ʈ�ѷ� ��ġ ������Ƽ
	UPROPERTY()
		FTransform l_handRepTrans;
	UPROPERTY()
		FTransform r_handRepTrans;
};
