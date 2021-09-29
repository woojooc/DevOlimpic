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

	// ����ƽ�޽� ���� �Ҵ�
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

	// ��Ƽ���� ���� �Ҵ�
	// ������
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

	// ������
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

	// �÷��̾� ��Ʈ�ѷ� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ASJ_PingPongPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ��� ����Ʈ ���÷��� ��ġ�� �ʱ� ��ġ���� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);

	// HMD ��ġ�� �������� �ٴ����� �����ϱ�
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

