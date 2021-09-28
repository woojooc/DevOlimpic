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

	// ī�޶�, ��Ʈ�ѷ� ��� �Ѹ� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Player)
		class USceneComponent* cameraRoot;

	// �÷��̾� ī�޶�
	UPROPERTY(EditAnywhere, Category = Player)
		class UCameraComponent* playerCam;

	// �÷��̾� ��
	UPROPERTY(EditAnywhere, Category = Player)
		class UStaticMeshComponent* playerFace;

	// �÷��̾� ����
	UPROPERTY(EditAnywhere, Category = Player)
		class UStaticMeshComponent* playerBody;

	// �÷��̾� �޼� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, Category = Player)
		class UMotionControllerComponent* leftController;

	// �÷��̾� �޼� ��(�⺻���� �ո� ���)
	UPROPERTY(EditAnywhere, Category = Player)
		class USkeletalMeshComponent* leftHand;

	// �÷��̾� ������ ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, Category = Player)
		class UMotionControllerComponent* rightController;

	// �÷��̾� ������ ��
	UPROPERTY(EditAnywhere, Category = Player)
		class USkeletalMeshComponent* rightHand;

	// �÷��̾� ������ ��(����)
	UPROPERTY(EditAnywhere, Category = Player)
		class UStaticMeshComponent* racket;

	// ���� ���ϵ�ȭ
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

	// ȣ��Ʈ�� Ŭ���̾�Ʈ�� �������ִ� ��ȣ(Host = 0, Client = 1)
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		int playerIndex;

	// �ʱ�ȭ Ÿ�̸�
	FTimerHandle resetHandle;

	// �ʱ�ȭ �Լ�
	void ResetHMD();

	// �ʱ�ȭ ����
	FRotator hmdRotation;
	FVector hmdLocation;

	// �÷��̾� �Ӹ� ȸ����
	FRotator headRotation;
	FVector headLocation;

};
