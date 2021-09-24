// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_HandActorComponent.h"
#include "SH_LobbyPlayer.h"
#include "SH_LobbyHandAnimInstance.h"
#include <Components/WidgetInteractionComponent.h>

// Sets default values for this component's properties
USH_HandActorComponent::USH_HandActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USH_HandActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� �޾ƿ���
	player = Cast<ASH_LobbyPlayer>(GetOwner());
	// �÷��̾ �����Ѵٸ�
	if (player)
	{
		// �޼� �ִϸ��̼� �ν��Ͻ� �޾ƿ���
		l_handAnim = Cast<USH_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
		// ������ �ִϸ��̼� �ν��Ͻ� �޾ƿ���
		r_handAnim = Cast<USH_LobbyHandAnimInstance>(player->rightHand->GetAnimInstance());
	}
}


// Ű ���� ���ε�
void USH_HandActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// �޼� ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &USH_HandActorComponent::GrabLeftHand);
	// �޼� ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &USH_HandActorComponent::OpenLeftHand);
	// ������ ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &USH_HandActorComponent::GrabRIghtHand);
	// ������ ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &USH_HandActorComponent::OpenRIghtHand);

	// A ��ư �����ÿ� �Լ� ���
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &USH_HandActorComponent::ButtonClick);
	// A ��ư �� �ÿ� �Լ� ���
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &USH_HandActorComponent::ButtonRelease);

}

// Called every frame
void USH_HandActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ��ư ���ۿ� ���� ��� �� ����

	// �޼� �ִϸ��̼� Ÿ�� ��� ���� ���� ������ ����
	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
	// ������ �ִϸ��̼� Ÿ�� ��� ���� ���� ������ ����
	r_handAnim->gripValue = FMath::Lerp(r_handAnim->gripValue, r_targetGripValue, gripSpeed * DeltaTime);
}

// �޼� ��� �ִϸ��̼� ����
void USH_HandActorComponent::GrabLeftHand()
{
	l_targetGripValue = 1.0f;
}

// �޼� ��� �ִϸ��̼� ����
void USH_HandActorComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;
}

// ������ ��� �ִϸ��̼� ����
void USH_HandActorComponent::GrabRIghtHand()
{
	r_targetGripValue = 1.0f;
}

// ������ ��� �ִϸ��̼� ����
void USH_HandActorComponent::OpenRIghtHand()
{
	r_targetGripValue = 0.0f;
}

void USH_HandActorComponent::ButtonClick()
{
	// ���� ���ͷ��� �������� Ŭ�� ������ Ű ���� ���콺 ���� ��ư Ŭ������ ����
	// �� ���� ��ư�� �����Ͱ� ���� ȿ���� �ش�.
	player->widgetPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void USH_HandActorComponent::ButtonRelease()
{
	player->widgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}

