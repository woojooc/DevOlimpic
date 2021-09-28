// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_LobbyPlayer.h"
#include <Components/CapsuleComponent.h>
#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "SH_HandActorComponent.h"
#include <Components/WidgetInteractionComponent.h>

// 언리얼 네트워크 헤더 추가
#include "Net/UnrealNetwork.h"
#include <Components/TextRenderComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
ASH_LobbyPlayer::ASH_LobbyPlayer()
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


	// 3D 텍스트 컴포넌트를 손목 위에 붙이기
	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftController);
	// 글씨 크기
	leftLog->SetWorldSize(20);
	// 글씨 정렬(가운데 정렬)
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	// 글씨 색상
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


	// 위젯 상호작용 컴포넌트 생성
	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	// 컴포넌트 오른손에 붙이기
	widgetPointer->SetupAttachment(rightController);

}

// Called when the game starts or when spawned
void ASH_LobbyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASH_LobbyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	l_handRepTrans = leftController->GetComponentTransform();
	r_handRepTrans = rightController->GetComponentTransform();

	// 로컬플레이어라면
	if (IsLocallyControlled())
	{
		// 로컬플레이어가 서버가 아니라면
		if (!HasAuthority())
		{
			// 서버 함수 실행
			Server_HandMove(l_handRepTrans, r_handRepTrans);
		}
		// 서버라면
		else
		{
			// 곧바로 멀티캐스트 함수 실행
			Multi_HandMove(l_handRepTrans, r_handRepTrans);
		}
	}
}

// Called to bind functionality to input
void ASH_LobbyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	handComp->SetupPlayerInputComponent(PlayerInputComponent);

	// 테스트용 이동 함수 등록
	PlayerInputComponent->BindAxis("MotionControllerThumbRight_X", this, &ASH_LobbyPlayer::MoveHorizontal);
	PlayerInputComponent->BindAxis("MotionControllerThumbRight_Y", this, &ASH_LobbyPlayer::MoveVertical);
}


// 테스트용 이동 함수
void ASH_LobbyPlayer::MoveHorizontal(float value)
{
	FVector dir = GetActorRightVector() * value;
	SetActorLocation(GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}
void ASH_LobbyPlayer::MoveVertical(float value)
{
	FVector dir = GetActorForwardVector() * value;
	SetActorLocation(GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

// 변수 동기화를 위한 함수 선언
void ASH_LobbyPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ASH_LobbyPlayer, l_handRepTrans);
	//DOREPLIFETIME(ASH_LobbyPlayer, r_handRepTrans);

	//DOREPLIFETIME(ASH_LobbyPlayer, r_handRepLoc);
	//DOREPLIFETIME(ASH_LobbyPlayer, r_handRepRot);
	//DOREPLIFETIME(ASH_LobbyPlayer, l_handRepLoc);
	//DOREPLIFETIME(ASH_LobbyPlayer, l_handRepRot);
}


bool ASH_LobbyPlayer::Server_HandMove_Validate(FTransform l_Trans, FTransform r_Trans)
{
	return true;
}

void ASH_LobbyPlayer::Server_HandMove_Implementation(FTransform l_Trans, FTransform r_Trans)
{
	// 멀티캐스트 실행
	Multi_HandMove(l_Trans, r_Trans);
}

bool ASH_LobbyPlayer::Multi_HandMove_Validate(FTransform l_Trans, FTransform r_Trans)
{
	return true;
}

void ASH_LobbyPlayer::Multi_HandMove_Implementation(FTransform l_Trans, FTransform r_Trans)
{

	if (!IsLocallyControlled())
	{
		// 클라이언트에서 받은 손 위치 함수를 전달
		leftController->SetWorldTransform(l_Trans);;
		rightController->SetWorldTransform(r_Trans);
	}

}
