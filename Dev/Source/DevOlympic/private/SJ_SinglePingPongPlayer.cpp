// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SinglePingPongPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/ChildActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_SingleModeSelectUIPannel.h"
#include "SJ_SinglePlayerHandComponent.h"
#include <Components/WidgetInteractionComponent.h>
#include"WJ_GameOverUI.h"

// Sets default values
ASJ_SinglePingPongPlayer::ASJ_SinglePingPongPlayer()
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

	// �÷��̾� ��
	playerFace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerFace"));
	playerFace->SetupAttachment(cameraRoot);

	// �÷��̾� ����
	playerBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerBody"));
	playerBody->SetupAttachment(cameraRoot);

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
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));

	// ������ ����
	racket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Racket"));
	racket->SetupAttachment(rightHand);

	handComp = CreateDefaultSubobject<USJ_SinglePlayerHandComponent>(TEXT("HandComponent"));

	// �޼� ������
	razer = CreateDefaultSubobject<UChildActorComponent>(TEXT("RazerComponent"));
	razer->SetupAttachment(leftController);

	// ���� ��ȣ�ۿ� ������Ʈ ����
	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	// ������Ʈ �����տ� ���̱�
	widgetPointer->SetupAttachment(leftController);
}

// Called when the game starts or when spawned
void ASJ_SinglePingPongPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// ��� ����Ʈ ���÷��� ��ġ�� �ʱ� ��ġ���� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);

	// HMD ��ġ�� �������� �ٴ����� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	GetWorldTimerManager().SetTimer(resetHandle, this, &ASJ_SinglePingPongPlayer::ResetHMD, 2.0f);

	singleModeUI = Cast<ASJ_SingleModeSelectUIPannel>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_SingleModeSelectUIPannel::StaticClass()));

	menuUI = Cast<AWJ_GameOverUI>(UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_GameOverUI::StaticClass()));

	menuUI->HideUI();

	razer->SetHiddenInGame(true);
}

// Called every frame
void ASJ_SinglePingPongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASJ_SinglePingPongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	handComp->SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("ShowUI", IE_Pressed, this, &ASJ_SinglePingPongPlayer::ShowUI);
}

void ASJ_SinglePingPongPlayer::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASJ_SinglePingPongPlayer::ShowUI()
{
	if (singleModeUI->isActive == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Show"));
		razer->SetHiddenInGame(false);
		singleModeUI->ShowUI();
		menuUI->Show();
	}
	else if (singleModeUI->isActive == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hide"));
		razer->SetHiddenInGame(true);
		singleModeUI->HideUI();
		menuUI->HideUI();
	}
}
