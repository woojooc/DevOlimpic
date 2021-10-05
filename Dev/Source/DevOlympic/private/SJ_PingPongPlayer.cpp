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
// �𸮾� ��Ʈ��ũ ��� �߰�
#include "Net/UnrealNetwork.h"

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

	// �޼� ������
	razer = CreateDefaultSubobject<UChildActorComponent>(TEXT("RazerComponent"));
	razer->SetupAttachment(leftController);

	selectComp = CreateDefaultSubobject<USJ_SelectUIComponent>(TEXT("Select Component"));
	playerRepComp = CreateDefaultSubobject<USH_PlayerReplicateComponent>(TEXT("ReplicateComponent"));

	// ���� ��ȣ�ۿ� ������Ʈ ����
	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	// ������Ʈ �����տ� ���̱�
	widgetPointer->SetupAttachment(leftController);

	//// �ε��� �Ҵ�
	//// �������̶��
	//if (HasAuthority())
	//{
	//	// �� �÷��̾���
	//	if (IsLocallyControlled())
	//	{
	//		// ��ȣ 0�� �Ҵ�
	//		playerIndex = 0;
	//	}
	//	// �ʴ�� Ŭ���̾�Ʈ �÷��̾���
	//	else
	//	{
	//		// ��ȣ 0�� �Ҵ�
	//		playerIndex = 1;
	//	}
	//}
	//// Ŭ���̾�Ʈ ���̶��
	//else
	//{
	//	// �� �÷��̾���
	//	if (IsLocallyControlled())
	//	{
	//		// ��ȣ 1�� �Ҵ�
	//		playerIndex = 1;
	//	}
	//	// ������ �濡 �ִ� ���� �÷��̾���
	//	else
	//	{
	//		// ��ȣ 0�� �Ҵ�
	//		playerIndex = 0;
	//	}
	//}

	/*
	// ����ƽ�޽� ���� �Ҵ�
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
			playerBody->SetMaterial(0,marioBody.Object);
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
	*/

	//// �÷��̾� ��Ʈ�ѷ� ����
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

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

