// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SinglePlayerHandComponent.h"
#include "SJ_SinglePingPongPlayer.h"
#include "WJ_LobbyHandAnimInstance.h"
#include <Components/WidgetInteractionComponent.h>

// Sets default values for this component's properties
USJ_SinglePlayerHandComponent::USJ_SinglePlayerHandComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USJ_SinglePlayerHandComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	player = Cast<ASJ_SinglePingPongPlayer>(GetOwner());
	l_handAnim = Cast<UWJ_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
	
}


// Called every frame
void USJ_SinglePlayerHandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
}

void USJ_SinglePlayerHandComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &USJ_SinglePlayerHandComponent::GrabLeftHand);

	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &USJ_SinglePlayerHandComponent::OpenLeftHand);
}

void USJ_SinglePlayerHandComponent::GrabLeftHand()
{
	l_targetGripValue = 1.0f;

	player->widgetPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void USJ_SinglePlayerHandComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;

	player->widgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}

