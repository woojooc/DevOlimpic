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

	// 플레이어 캡슐 콜라이더 
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	capsuleComp->SetCapsuleRadius(40.0f);

	// VR 관련 컴포넌트 담는 뿌리 컴포넌트
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(RootComponent);
	cameraRoot->SetRelativeLocation(FVector(0, 0, 40.0f));

	// 플레이어 카메라
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	playerCam->SetupAttachment(cameraRoot);

	// 플레이어 얼굴
	playerFace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerFace"));
	playerFace->SetupAttachment(cameraRoot);

	// 플레이어 몸통
	playerBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerBody"));
	playerBody->SetupAttachment(cameraRoot);

	// 왼손 컨트롤러
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionContoller"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	// 오른손 컨트롤러
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionContoller"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	// 왼손 모델
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));

	// 오른손 모델
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));

	// 오른손 라켓
	racket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Racket"));
	racket->SetupAttachment(rightHand);

	handComp = CreateDefaultSubobject<USJ_SinglePlayerHandComponent>(TEXT("HandComponent"));

	// 왼손 레이저
	razer = CreateDefaultSubobject<UChildActorComponent>(TEXT("RazerComponent"));
	razer->SetupAttachment(leftController);

	// 위젯 상호작용 컴포넌트 생성
	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	// 컴포넌트 오른손에 붙이기
	widgetPointer->SetupAttachment(leftController);
}

// Called when the game starts or when spawned
void ASJ_SinglePingPongPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 헤드 마운트 디스플레이 장치의 초기 위치값을 설정하기
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);

	// HMD 장치의 기준점을 바닥으로 설정하기
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
