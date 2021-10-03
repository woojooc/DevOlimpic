// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SelectUIComponent.h"
#include "SJ_PingPongPlayer.h"
#include "WJ_LobbyHandAnimInstance.h"
#include <Components/WidgetInteractionComponent.h>

// Sets default values for this component's properties
USJ_SelectUIComponent::USJ_SelectUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USJ_SelectUIComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ASJ_PingPongPlayer>(GetOwner());

	l_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
}


// Called every frame
void USJ_SelectUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 왼손 애니메이션 타겟 밸류 값에 따라 움직임 조정
	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
}

void USJ_SelectUIComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 왼손 잡기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &USJ_SelectUIComponent::GrabLeftHand);
	// 왼손 펴기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &USJ_SelectUIComponent::OpenLeftHand);
}

void USJ_SelectUIComponent::GrabLeftHand()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClick"))
	l_targetGripValue = 1.0f;

	player->widgetPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void USJ_SelectUIComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;

	player->widgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}

void USJ_SelectUIComponent::ButtonClick()
{
	
}

void USJ_SelectUIComponent::ButtonRelease()
{
	
}

