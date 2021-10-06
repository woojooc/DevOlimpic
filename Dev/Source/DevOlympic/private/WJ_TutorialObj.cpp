#include "WJ_TutorialObj.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_LobbyPlayer.h"
#include <Camera/CameraComponent.h>
#include "Kismet/KismetMathLibrary.h"

AWJ_TutorialObj::AWJ_TutorialObj()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWJ_TutorialObj::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorEnableCollision(false);
	player = Cast<AWJ_LobbyPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(),AWJ_LobbyPlayer::StaticClass()));
	playerCam = Cast<UCameraComponent>(player->GetDefaultSubobjectByName(TEXT("MainCamera")));
}

void AWJ_TutorialObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bCanEyeTrace == true)
	{
		FVector location = GetActorLocation();
		FVector camLocation = playerCam->GetComponentLocation();

		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(location, camLocation);
		rotator.Roll = GetActorRotation().Roll;
		rotator.Yaw += 180;
		SetActorRotation(rotator);
	}
}

