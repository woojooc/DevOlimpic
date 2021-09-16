// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SJ_PingPongPlayer.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_PingPongPlayer : public APawn
{
	GENERATED_BODY()

	// �÷��̾� �ݶ��̴�
	UPROPERTY(EditAnywhere, Category = Player)
	class UCapsuleComponent* capsuleComp;

	// ī�޶�, ��Ʈ�ѷ� ��� �Ѹ� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Player)
	class USceneComponent* cameraRoot;

	// �÷��̾� ī�޶�
	UPROPERTY(EditAnywhere, Category = Player)
	class UCameraComponent* playerCam;

	// �÷��̾� �޼� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, Category = Player)
	class UMotionControllerComponent* leftController;

	// �÷��̾� �޼� ��(�⺻���� �ո� ���)
	UPROPERTY(EditAnywhere, Category = Player)
	class USkeletalMeshComponent* leftHand;

	// �÷��̾� ������ ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, Category = Player)
	class UMotionControllerComponent* rightController;

	// �÷��̾� ������ ��(����)
	UPROPERTY(EditAnywhere, Category = Player)
	class UStaticMeshComponent* racket;

public:
	// Sets default values for this pawn's properties
	ASJ_PingPongPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	// �ʱ�ȭ Ÿ�̸�
	FTimerHandle resetHandle;

	// �ʱ�ȭ �Լ�
	void ResetHMD();

	FRotator hmdRotation;
	FVector hmdLocation;
};
