// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_LobbyPlayer.h"
#include <Components/CapsuleComponent.h>
#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "WJ_HandActorComponent.h"
#include <Components/TextRenderComponent.h>
#include <Components/WidgetInteractionComponent.h>

// Sets default values
AWJ_LobbyPlayer::AWJ_LobbyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	capsuleComp->SetCapsuleRadius(40.0f);
	capsuleComp->SetCollisionProfileName(TEXT("LobbyPlayer"));

	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	cameraRoot->SetupAttachment(RootComponent);
	cameraRoot->SetRelativeLocation(FVector(0, 0, 30.0f));

	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	playerCam->SetupAttachment(cameraRoot);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));

	// ���� ������Ʈ
	// �ڵ� ���� ������Ʈ
	handComp = CreateDefaultSubobject<UWJ_HandActorComponent>(TEXT("Hand Component"));

	// 3D �ؽ�Ʈ ������Ʈ�� �ո� ���� ���̱�
	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftController);
	// �۾� ũ��
	leftLog->SetWorldSize(20);
	// �۾� ����(��� ����)
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	// �۾� ����
	leftLog->SetTextRenderColor(FColor::Yellow);
	leftLog->SetRelativeRotation(FRotator(0, 180.0f, 0));
	leftLog->SetRelativeLocation(FVector(0, 0, 40.f));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightController);
	rightLog->SetWorldSize(20);
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetTextRenderColor(FColor::Yellow);
	rightLog->SetRelativeRotation(FRotator(0, 180.0f, 0));
	rightLog->SetRelativeLocation(FVector(0, 0, 40.f));


	// ���� ��ȣ�ۿ� ������Ʈ ����
	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	// ������Ʈ �����տ� ���̱�
	widgetPointer->SetupAttachment(leftController);
}

// Called when the game starts or when spawned
void AWJ_LobbyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWJ_LobbyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWJ_LobbyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	handComp->SetupPlayerInputComponent(PlayerInputComponent);
}

