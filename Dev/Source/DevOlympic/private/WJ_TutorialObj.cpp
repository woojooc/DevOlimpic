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

	maxScale = GetActorScale3D();
	minScale = maxScale * 0.6;
	SetActorScale3D(minScale);
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

	if (bOpen)
	{
		Open();
	}

	if (bClose)
	{
		Close();
	}
}

void AWJ_TutorialObj::SetOpen()
{
	bOpen = true;
}

void AWJ_TutorialObj::SetClose()
{
	bClose = true;
}

void AWJ_TutorialObj::Open()
{
	FVector scale = FMath::Lerp(scale, maxScale,0.5);

	float dist = FVector::Dist(scale, maxScale);
	if (dist < 10)
	{
		scale = maxScale;
		bOpen = false;
	}
	SetActorScale3D(scale);
}

void AWJ_TutorialObj::Close()
{
	FVector scale = FMath::Lerp(scale, minScale, 0.5);

	float dist = FVector::Dist(scale, minScale);
	if (dist < 10)
	{
		scale = minScale;
		bClose = false;

		// 다 작아지면 SetHidden true
		SetHidden(true);
	}
	SetActorScale3D(scale);
}

