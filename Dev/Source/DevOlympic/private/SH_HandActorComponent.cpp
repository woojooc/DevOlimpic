// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_HandActorComponent.h"
#include "SH_LobbyPlayer.h"
#include "SH_LobbyHandAnimInstance.h"

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

	// 플레이어 받아오기
	player = Cast<ASH_LobbyPlayer>(GetOwner());
	// 플레이어가 존재한다면
	if (player)
	{
		// 왼손 애니메이션 인스턴스 받아오기
		l_handAnim = Cast<USH_LobbyHandAnimInstance>(player->leftHand->GetAnimInstance());
		// 오른손 애니메이션 인스턴스 받아오기
		r_handAnim = Cast<USH_LobbyHandAnimInstance>(player->rightHand->GetAnimInstance());
	}
}


// 키 조작 바인딩
void USH_HandActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 왼손 잡기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &USH_HandActorComponent::GrabLeftHand);
	// 왼손 펴기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &USH_HandActorComponent::OpenLeftHand);
	// 오른손 잡기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &USH_HandActorComponent::GrabRIghtHand);
	// 오른손 펴기 애니메이션 실행
	PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &USH_HandActorComponent::OpenRIghtHand);
}

// Called every frame
void USH_HandActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 버튼 조작에 따라 밸류 값 조정

	// 왼손 애니메이션 타겟 밸류 값에 따라 움직임 조정
	l_handAnim->gripValue = FMath::Lerp(l_handAnim->gripValue, l_targetGripValue, gripSpeed * DeltaTime);
	// 오른손 애니메이션 타겟 밸류 값에 따라 움직임 조정
	r_handAnim->gripValue = FMath::Lerp(r_handAnim->gripValue, r_targetGripValue, gripSpeed * DeltaTime);
}

// 왼손 잡기 애니메이션 실행
void USH_HandActorComponent::GrabLeftHand()
{
	l_targetGripValue = 1.0f;
}

// 왼손 펴기 애니메이션 실행
void USH_HandActorComponent::OpenLeftHand()
{
	l_targetGripValue = 0.0f;
}

// 오른손 잡기 애니메이션 실행
void USH_HandActorComponent::GrabRIghtHand()
{
	r_targetGripValue = 1.0f;
}

// 오른손 펴기 애니메이션 실행
void USH_HandActorComponent::OpenRIghtHand()
{
	r_targetGripValue = 0.0f;
}

