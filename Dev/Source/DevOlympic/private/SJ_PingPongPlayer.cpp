// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PingPongPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/ChildActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_GameOverUI.h"
#include "SJ_SelectUIComponent.h"
#include <Components/WidgetInteractionComponent.h>
#include "VRGameModeBase.h"
#include "SH_PlayerReplicateComponent.h"
// 언리얼 네트워크 헤더 추가
#include "Net/UnrealNetwork.h"

// Sets default values
ASJ_PingPongPlayer::ASJ_PingPongPlayer()
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

	// 왼손 레이저
	razer = CreateDefaultSubobject<UChildActorComponent>(TEXT("RazerComponent"));
	razer->SetupAttachment(leftController);

	selectComp = CreateDefaultSubobject<USJ_SelectUIComponent>(TEXT("Select Component"));
	playerRepComp = CreateDefaultSubobject<USH_PlayerReplicateComponent>(TEXT("ReplicateComponent"));

	// 위젯 상호작용 컴포넌트 생성
	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	// 컴포넌트 오른손에 붙이기
	widgetPointer->SetupAttachment(leftController);

	//// 인덱스 할당
	//// 서버방이라면
	//if (HasAuthority())
	//{
	//	// 내 플레이어라면
	//	if (IsLocallyControlled())
	//	{
	//		// 번호 0번 할당
	//		playerIndex = 0;
	//	}
	//	// 초대된 클라이언트 플레이어라면
	//	else
	//	{
	//		// 번호 0번 할당
	//		playerIndex = 1;
	//	}
	//}
	//// 클라이언트 방이라면
	//else
	//{
	//	// 내 플레이어라면
	//	if (IsLocallyControlled())
	//	{
	//		// 번호 1번 할당
	//		playerIndex = 1;
	//	}
	//	// 기존에 방에 있던 서버 플레이어라면
	//	else
	//	{
	//		// 번호 0번 할당
	//		playerIndex = 0;
	//	}
	//}

	/*
	// 스태틱메쉬 동적 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> face(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if (face.Succeeded())
	{
		playerFace->SetStaticMesh(face.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>body(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));

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
			playerBody->SetMaterial(0,marioBody.Object);
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
	*/

	//// 플레이어 컨트롤러 빙의
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ASJ_PingPongPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 헤드 마운트 디스플레이 장치의 초기 위치값을 설정하기
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);

	// HMD 장치의 기준점을 바닥으로 설정하기
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	GetWorldTimerManager().SetTimer(resetHandle, this, &ASJ_PingPongPlayer::ResetHMD, 2.0f);

	// gameOverUI = Cast<AWJ_GameOverUI>(UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_GameOverUI::StaticClass()));

	TArray<AActor*> bpGameOverUI;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_GameOverUI::StaticClass(), bpGameOverUI);

	if (bpGameOverUI.Num() > 0)
	{
		for (int i = 0; i < bpGameOverUI.Num(); i++)
		{
			AWJ_GameOverUI* emptyPlace = nullptr;
			gameOverUI.Add(emptyPlace);
		}

		for (int i = 0; i < bpGameOverUI.Num(); i++)
		{
			auto ui = Cast<AWJ_GameOverUI>(bpGameOverUI[i]);
			gameOverUI[ui->id] = ui;
		}
	}
	gameMode = Cast<AVRGameModeBase>(GetWorld()->GetGameState());

	razer->SetHiddenInGame(true);

	if (playerIndex == 0)
	{
		playerFace->SetMaterial(0, marioFace);
		playerBody->SetMaterial(0, marioBody);
	}
	else if (playerIndex == 1)
	{

		playerFace->SetMaterial(0, luigiFace);
		playerBody->SetMaterial(0, luigiBody);
	}
}

// Called every frame
void ASJ_PingPongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(headRotation, headLocation);

	playerFace->SetRelativeRotation(headRotation);

	if (gameMode->levelState == EPPLevelState::GameOver)
	{
		razer->SetHiddenInGame(false);
	}
}

// Called to bind functionality to input
void ASJ_PingPongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	selectComp->SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ShowUI", IE_Pressed, this, &ASJ_PingPongPlayer::ShowUI);
}

void ASJ_PingPongPlayer::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASJ_PingPongPlayer::ShowUI()
{
	/*
	if (playerIndex == 0)
	{
		if (gameOverUI[0]->isActive == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("ShowUI"));
			razer->SetHiddenInGame(false);
			gameOverUI[0]->Show();
		}
		else if (gameOverUI[0]->isActive == true)
		{
			razer->SetHiddenInGame(true);
			gameOverUI[0]->HideUI();
		}
	}
	else if (playerIndex == 1)
	{
		if (gameOverUI[1]->isActive == false)
		{
			gameOverUI[1]->Show();
		}
		else if (gameOverUI[1]->isActive == true)
		{
			gameOverUI[1]->HideUI();
		}
	}
	*/
	if (gameOverUI[playerIndex]->isActive == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowUI"));
		razer->SetHiddenInGame(false);
		gameOverUI[playerIndex]->Show();
	}
	else if (gameOverUI[playerIndex]->isActive == true)
	{
		razer->SetHiddenInGame(true);
		gameOverUI[playerIndex]->HideUI();
	}
}

