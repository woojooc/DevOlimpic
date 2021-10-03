#include "WJ_LbMoveActorComponent.h"
#include "WJ_LobbyPlayer.h"
#include "MotionControllerComponent.h"


UWJ_LbMoveActorComponent::UWJ_LbMoveActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWJ_LbMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AWJ_LobbyPlayer>(GetOwner());

}


void UWJ_LbMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWJ_LbMoveActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MotionControllerThumbLeft_X", this, &UWJ_LbMoveActorComponent::MoveHorizontal);
	PlayerInputComponent->BindAxis("MotionControllerThumbLeft_Y", this, &UWJ_LbMoveActorComponent::MoveVertical);
}

void UWJ_LbMoveActorComponent::MoveHorizontal(float value)
{
	if (player == nullptr)
	{
		return;
	}

	FVector dir = player->GetActorRightVector() * value;
	player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}
void UWJ_LbMoveActorComponent::MoveVertical(float value)
{
	if (player == nullptr)
	{
		return;
	}

	FVector dir = player->GetActorForwardVector() * value;
	player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}