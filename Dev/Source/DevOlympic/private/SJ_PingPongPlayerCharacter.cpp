// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PingPongPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/ChildActorComponent.h"

// Sets default values
ASJ_PingPongPlayerCharacter::ASJ_PingPongPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	// 스태틱메쉬 동적 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> face(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if (face.Succeeded())
	{
		playerFace->SetStaticMesh(face.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>body(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));

	if (body.Succeeded())
	{
		playerBody->SetStaticMesh(body.Object);
	}

	// 머티리얼 동적 할당
	// 마리오
	ConstructorHelpers::FObjectFinder<UMaterial> marioface(TEXT("Material'/Game/SJ/Blueprints/PingPong/PingPongPlayer/MarioFace_Mat.MarioFace_Mat'"));

	if (playerIndex == 0)
	{
		if (marioface.Succeeded())
		{
			playerFace->SetMaterial(0, marioface.Object);
		}
	}

	ConstructorHelpers::FObjectFinder<UMaterial> marioBody(TEXT("Material'/Game/SJ/Blueprints/PingPong/PingPongPlayer/Red_Mat.Red_Mat'"));

	if (playerIndex == 0)
	{
		if (marioBody.Succeeded())
		{
			playerBody->SetMaterial(0, marioBody.Object);
		}
	}

	// 루이지
	ConstructorHelpers::FObjectFinder<UMaterial> luigiFace(TEXT("Material'/Game/SJ/Blueprints/PingPong/PingPongPlayer/Luigi_Mat.Luigi_Mat'"));
	if (playerIndex == 1)
	{
		if (luigiFace.Succeeded())
		{
			playerFace->SetMaterial(0, luigiFace.Object);
		}
	}

	ConstructorHelpers::FObjectFinder<UMaterial> luigiBody(TEXT("Material'/Game/SJ/Blueprints/PingPong/PingPongPlayer/Green_Mat.Green_Mat'"));
	if (playerIndex == 1)
	{
		if (luigiBody.Succeeded())
		{
			playerBody->SetMaterial(0, luigiBody.Object);
		}
	}

	// 플레이어 컨트롤러 빙의
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ASJ_PingPongPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 헤드 마운트 디스플레이 장치의 초기 위치값을 설정하기
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);

	// HMD 장치의 기준점을 바닥으로 설정하기
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	GetWorldTimerManager().SetTimer(resetHandle, this, &ASJ_PingPongPlayerCharacter::ResetHMD, 2.0f);
}

// Called every frame
void ASJ_PingPongPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	playerFace->SetRelativeRotation(headRotation);
}

// Called to bind functionality to input
void ASJ_PingPongPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASJ_PingPongPlayerCharacter::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

