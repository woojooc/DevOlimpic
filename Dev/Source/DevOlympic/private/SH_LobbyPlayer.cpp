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

// �𸮾� ��Ʈ��ũ ��� �߰�
#include "Net/UnrealNetwork.h"
#include <Components/TextRenderComponent.h>

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

	// ���� ������Ʈ
	// �ڵ� ���� ������Ʈ
	handComp = CreateDefaultSubobject<USH_HandActorComponent>(TEXT("Hand Component"));


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

	FString l_str = FString::Printf(TEXT("%.1f %.1f %.1f"), leftController->GetComponentLocation().X, leftController->GetComponentLocation().Y, leftController->GetComponentLocation().Z);
	leftLog->SetText(FText::FromString(l_str));
	FString r_str = FString::Printf(TEXT("%.1f %.1f %.1f"), rightController->GetComponentLocation().X, rightController->GetComponentLocation().Y, rightController->GetComponentLocation().Z);
	rightLog->SetText(FText::FromString(r_str));

	////UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), leftController->GetComponentLocation().X, leftController->GetComponentLocation().Y, leftController->GetComponentLocation().Z);
	//l_handRepTrans = leftController->GetComponentTransform();
	//r_handRepTrans = rightController->GetComponentTransform();


	l_handRepLoc = leftController->GetComponentLocation();
	l_handRepRot = leftController->GetComponentRotation();
	r_handRepLoc = rightController->GetComponentLocation();
	r_handRepRot = rightController->GetComponentRotation();


	// ���� ����(�÷��̾�)�� �ƴ϶��
	if (!IsLocallyControlled())
	{
		//FString l_str = FString::Printf(TEXT("%s"), "guest left");
		//leftLog->SetText(FText::FromString(l_str));
		//FString r_str = FString::Printf(TEXT("%s"), "guest right");
		//rightLog->SetText(FText::FromString(l_str));


		//// �� ��ġ�� ������Ʈ ���ش�
		//leftController->SetWorldTransform(l_handRepTrans);
		//rightController->SetWorldTransform(r_handRepTrans);

		leftController->SetWorldLocation(l_handRepLoc);
		leftController->SetWorldRotation(l_handRepRot);
		rightController->SetWorldLocation(r_handRepLoc);
		rightController->SetWorldRotation(r_handRepRot);


		//FString l_str = FString::Printf(TEXT("%.1f %.1f %.1f"), leftController->GetComponentLocation().X, leftController->GetComponentLocation().Y, leftController->GetComponentLocation().Z);
		//leftLog->SetText(FText::FromString(l_str));
		//FString r_str = FString::Printf(TEXT("%.1f %.1f %.1f"), rightController->GetComponentLocation().X, rightController->GetComponentLocation().Y, rightController->GetComponentLocation().Z);
		//rightLog->SetText(FText::FromString(r_str));
		FString l_str_rep = FString::Printf(TEXT("%.1f %.1f %.1f"), l_handRepLoc.X, l_handRepLoc.Y, l_handRepLoc.Z);
		leftLog->SetText(FText::FromString(l_str_rep));
		FString r_str_rep = FString::Printf(TEXT("%.1f %.1f %.1f"), r_handRepLoc.X, r_handRepLoc.Y, r_handRepLoc.Z);
		rightLog->SetText(FText::FromString(r_str_rep));
	}
}

// Called to bind functionality to input
void ASH_LobbyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	handComp->SetupPlayerInputComponent(PlayerInputComponent);


	// �׽�Ʈ�� �̵� �Լ� ���
	PlayerInputComponent->BindAxis("MotionControllerThumbRight_X", this, &ASH_LobbyPlayer::MoveHorizontal);
	PlayerInputComponent->BindAxis("MotionControllerThumbRight_Y", this, &ASH_LobbyPlayer::MoveVertical);
}


// �׽�Ʈ�� �̵� �Լ�
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

// ���� ����ȭ�� ���� �Լ� ����
void ASH_LobbyPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ASH_LobbyPlayer, l_handRepTrans);
	//DOREPLIFETIME(ASH_LobbyPlayer, r_handRepTrans);
	DOREPLIFETIME(ASH_LobbyPlayer, r_handRepLoc);
	DOREPLIFETIME(ASH_LobbyPlayer, r_handRepRot);
	DOREPLIFETIME(ASH_LobbyPlayer, l_handRepLoc);
	DOREPLIFETIME(ASH_LobbyPlayer, l_handRepRot);
}