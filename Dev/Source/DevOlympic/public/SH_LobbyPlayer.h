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
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	class USH_HandActorComponent* handComp;


	// ���� ��ȣ�ۿ� ������
	UPROPERTY(EditAnywhere, Category = VideoInteractions)
		class UWidgetInteractionComponent* widgetPointer;


	// ���� ����ȭ�� ���� ����
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;


	// �� ��ġ ������ ����ȭ
	// �޼� ��ġ ����ȭ ����
	UPROPERTY(Replicated, BlueprintReadWrite)
		FTransform l_handRepTrans;

	// ������ ��ġ ����ȭ ����
	UPROPERTY(Replicated)
		FTransform r_handRepTrans;
};
