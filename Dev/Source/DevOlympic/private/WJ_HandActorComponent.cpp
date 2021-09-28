// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_HandActorComponent.h"
#include "WJ_LobbyPlayer.h"
#include "WJ_LobbyHandAnimInstance.h"
#include <Components/WidgetInteractionComponent.h>

// Sets default values for this component's properties
UWJ_HandActorComponent::UWJ_HandActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UWJ_HandActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� �޾ƿ���
	player = Cast<AWJ_LobbyPlayer>(GetOwner());
	// �÷��̾ �����Ѵٸ�
	if (player)
	{
		// �޼� �ִϸ��̼� �ν��Ͻ� �޾ƿ���
		l_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
		// ������ �ִϸ��̼� �ν��Ͻ� �޾ƿ���
		r_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->rightHand->GetAnimInstance());
	}
}


// Ű ���� ���ε�
void UWJ_HandActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// �޼� ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &UWJ_HandActorComponent::GrabLeftHand);
	// �޼� ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &UWJ_HandActorComponent::OpenLeftHand);
	// ������ ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &UWJ_HandActorComponent::GrabRIghtHand);
	// ������ ��� �ִϸ��̼� ����
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &UWJ_HandActorComponent::OpenRIghtHand);

	// A ��ư �����ÿ� �Լ� ���
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &UWJ_HandActorComponent::ButtonClick);
	// A ��ư �� �ÿ� �Լ� ���
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &UWJ_HandActorComponent::ButtonRelease);

}

// Called every frame
void UWJ_HandActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ��ư ���ۿ� ���� ��� �� ����

	// �޼� �ִϸ��̼� Ÿ�� ��� ���� ���� ������ ����
	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
	// ������ �ִϸ��̼� Ÿ�� ��� ���� ���� ������ ����
	r_handAnim->gripValue = FMath::Lerp(r_handAnim->gripValue, r_targetGripValue, gripSpeed * DeltaTime);
}

// �޼� ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::GrabLeftHand()
{
	l_targetGripValue = 1.0f;
}

// �޼� ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;
}

// ������ ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::GrabRIghtHand()
{
	r_targetGripValue = 1.0f;
}

// ������ ��� �ִϸ��̼� ����
void UWJ_HandActorComponent::OpenRIghtHand()
{
	r_targetGripValue = 0.0f;
}

void UWJ_HandActorComponent::ButtonClick()
{
	// ���� ���ͷ��� �������� Ŭ�� ������ Ű ���� ���콺 ���� ��ư Ŭ������ ����
	// �� ���� ��ư�� �����Ͱ� ���� ȿ���� �ش�.
	player->widgetPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void UWJ_HandActorComponent::ButtonRelease()
{
	player->widgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}

