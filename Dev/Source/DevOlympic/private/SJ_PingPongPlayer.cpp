// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PingPongPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
ASJ_PingPongPlayer::ASJ_PingPongPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �÷��̾� ĸ�� �ݶ��̴� 
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	capsuleComp->SetCapsuleRadius(40.0f);

	// VR ���� ������Ʈ ��� �Ѹ� ������Ʈ
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(RootComponent);
	cameraRoot->SetRelativeLocation(FVector(0, 0, 40.0f));

	// �÷��̾� ī�޶�
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	playerCam->SetupAttachment(cameraRoot);

	// �޼� ��Ʈ�ѷ�
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionContoller"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	// ������ ��Ʈ�ѷ�
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionContoller"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	// �޼� ��
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));

	// ������ ��
	racket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Racket"));
	racket->SetupAttachment(rightController);

	// �÷��̾� ��Ʈ�ѷ� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ASJ_PingPongPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// ��� ����Ʈ ���÷��� ��ġ�� �ʱ� ��ġ���� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);

	// HMD ��ġ�� �������� �ٴ����� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	GetWorldTimerManager().SetTimer(resetHandle, this, &ASJ_PingPongPlayer::ResetHMD, 2.0f);
}

// Called every frame
void ASJ_PingPongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASJ_PingPongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASJ_PingPongPlayer::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

