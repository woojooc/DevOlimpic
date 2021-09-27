// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_RoomPlayer.h"
#include <Components/CapsuleComponent.h>
#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "SH_HandActorComponent.h"


// 언리얼 네트워크 헤더 추가
#include "Net/UnrealNetwork.h"


// Sets default values
ASH_RoomPlayer::ASH_RoomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	capsuleComp->SetCapsuleRadius(40.0f);
	capsuleComp->SetCollisionProfileName(TEXT("VR_Player"));

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

	// 액터 컴포넌트
	// 핸드 액터 컴포넌트
	handComp = CreateDefaultSubobject<USH_HandActorComponent>(TEXT("Hand Component"));
}

// Called when the game starts or when spawned
void ASH_RoomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASH_RoomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	l_handRepTrans = leftController->GetComponentTransform();
	r_handRepTrans = rightController->GetComponentTransform();

	// 로컬 액터(플레이어)가 아니라면
	if (!IsLocallyControlled())
	{
		// 손 위치를 업데이트 해준다
		leftController->SetWorldTransform(l_handRepTrans);
		rightController->SetWorldTransform(r_handRepTrans);
	}
}

// Called to bind functionality to input
void ASH_RoomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 변수 동기화를 위한 함수 선언
void ASH_RoomPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	 

	DOREPLIFETIME(ASH_RoomPlayer, l_handRepTrans);
	DOREPLIFETIME(ASH_RoomPlayer, r_handRepTrans);
}