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

	// �÷��̾� �ݶ��̴�
	UPROPERTY(EditAnywhere, Category = Player)
		class UCapsuleComponent* capsuleComp;

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

	// ������
	UPROPERTY(EditAnywhere, Category = Player)
	class UChildActorComponent* razer;

	UPROPERTY(EditAnywhere, Category = Player)
	class USJ_SelectUIComponent* selectComp;

	UPROPERTY(EditAnywhere, Category = Player)
	class USH_PlayerReplicateComponent* playerRepComp;

	// ���� ��ȣ�ۿ� ������
	UPROPERTY(EditAnywhere, Category = WidgetInteraction)
	class UWidgetInteractionComponent* widgetPointer;

	// ���� ���
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

	// ĸ�� ī�޶�
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

	// ȣ��Ʈ�� Ŭ���̾�Ʈ�� �������ִ� ��ȣ(Host = 0, Client = 1)
	UPROPERTY(VisibleAnywhere, Category = PlayerSetting)
	int playerIndex;

	// �ʱ�ȭ Ÿ�̸�
	FTimerHandle resetHandle;

	// �ʱ�ȭ �Լ�
	void ResetHMD();

	void ShowUI();

	// ����� ��ġ �ʱ�ȭ ����
	FRotator hmdRotation;
	FVector hmdLocation;

	// HMD ȸ������ �÷��̾� �Ӹ��� �����ϴ� ����
	FRotator headRotation;
	FVector headLocation;
};
