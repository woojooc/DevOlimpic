// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SJ_PingPongSpectator.generated.h"

UENUM()
enum class EJumpState : uint8 
{
	Idle,
	Jump,
	Down
};

UCLASS()
class DEVOLYMPIC_API ASJ_PingPongSpectator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASJ_PingPongSpectator();

	// ���� �ݶ��̴�
	UPROPERTY(EditAnywhere, Category = Spectator)
	class UCapsuleComponent* capComp;

	// �Ѹ� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Spectator)
	class USceneComponent* root;

	// ���� ��
	UPROPERTY(EditAnywhere, Category = Spectator)
	class UStaticMeshComponent* face;

	// ���� ����
	UPROPERTY(EditAnywhere, Category = Spectator)
	class UStaticMeshComponent* body;

	// ���� ������
	UPROPERTY(EditAnywhere, Category = Spectator)
	class USkeletalMeshComponent* rightHand;

	// ���� �޼�
	UPROPERTY(EditAnywhere, Category = Spectator)
	class USkeletalMeshComponent* leftHand;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	UPROPERTY()
	FVector IdlePos;

	UPROPERTY()
	FVector jumpPos;

	UPROPERTY()
	FVector downPos;

	UPROPERTY()
	float jumpPower = 500;

	UPROPERTY()
	float randomFirstTime;

	UPROPERTY()
	float randomTime;

	FTimerHandle firstJumpTimer;
	FTimerHandle jumpTimer;

	EJumpState j_State = EJumpState::Idle;

	void Idle();
	void Jump();
	void Down();

	void JumpUp();
};
