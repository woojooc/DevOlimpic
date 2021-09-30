// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_PlayerReplicateComponent.h"
#include <GameFramework/Pawn.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>

// �𸮾� ��Ʈ��ũ ��� �߰�
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USH_PlayerReplicateComponent::USH_PlayerReplicateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USH_PlayerReplicateComponent::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� ������Ʈ �޾ƿ���
	player = Cast<APawn>(GetOwner());
	// ī�޶� ������Ʈ �޾ƿ���
	playerCam = Cast<UCameraComponent>(player->GetDefaultSubobjectByName(TEXT("MainCamera")));
	// �޼�, ������ ��Ʈ�ѷ� �޾ƿ���
	leftController = Cast<UMotionControllerComponent>(player->GetDefaultSubobjectByName(TEXT("LeftMotionController")));
	rightController = Cast<UMotionControllerComponent>(player->GetDefaultSubobjectByName(TEXT("RightMotionController")));



}


// Called every frame
void USH_PlayerReplicateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ��ġ ����ȭ �� �����Ӹ��� ����
	UpdateReplicate();
}

void USH_PlayerReplicateComponent::UpdateReplicate()
{

	// �����÷��̾���
	if (player->IsLocallyControlled())
	{
		player_Tr = player->GetActorTransform();
		playerCam_Tr = playerCam->GetComponentTransform();
		leftController_Tr = leftController->GetComponentTransform();
		rightController_Tr = rightController->GetComponentTransform();

		// �����÷��̾ ������ �ƴ϶��
		if (!player->HasAuthority())
		{
			// ���� �Լ� ����
			Server_UpdateReplicate(player_Tr, playerCam_Tr, leftController_Tr, rightController_Tr);
		}
		// �������
		else
		{
			// ��ٷ� ��Ƽĳ��Ʈ �Լ� ����
			Multi_UpdateReplicate(player_Tr, playerCam_Tr, leftController_Tr, rightController_Tr);
		}
	}
}

bool USH_PlayerReplicateComponent::Server_UpdateReplicate_Validate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr)
{
	return true;
}

void USH_PlayerReplicateComponent::Server_UpdateReplicate_Implementation(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr)
{
	Multi_UpdateReplicate_Implementation(playerTr, cameraTr, lcontTr, rcontTr);
}

bool USH_PlayerReplicateComponent::Multi_UpdateReplicate_Validate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr)
{
	return true;
}

void USH_PlayerReplicateComponent::Multi_UpdateReplicate_Implementation(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr)
{
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!player)
	{
		player = Cast<APawn>(GetOwner());
	}
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!playerCam)
	{
		playerCam = Cast<UCameraComponent>(player->GetDefaultSubobjectByName(TEXT("MainCamera")));
	}
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!leftController)
	{
		leftController = Cast<UMotionControllerComponent>(player->GetDefaultSubobjectByName(TEXT("LeftMotionController")));
	}
	// ��Ƽĳ��Ʈ ������ ������Ʈ ���� ó��
	if (!rightController)
	{
		rightController = Cast<UMotionControllerComponent>(player->GetDefaultSubobjectByName(TEXT("RightMotionController")));
	}
	// ���� ���� �÷��̾ �ƴ϶��
	if (!player->IsLocallyControlled())
	{
		// Ŭ���̾�Ʈ���� ���� �� ��ġ �Լ��� ����
		// �÷��̾� ���� ��ġ
		player->SetActorTransform(playerTr);
		// ī�޶� ������Ʈ
		playerCam->SetWorldTransform(cameraTr);
		// �޼�, ������ ��Ʋ�ѷ�
		leftController->SetWorldTransform(lcontTr);
		rightController->SetWorldTransform(rcontTr);
	}
}