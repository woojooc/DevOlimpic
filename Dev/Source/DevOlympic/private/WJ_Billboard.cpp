#include "WJ_Billboard.h"
#include <Components/TextRenderComponent.h>
#include <Kismet/GameplayStatics.h>
#include "WJ_LobbyPlayer.h"
#include <Camera/CameraComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/SceneCaptureComponent2D.h>

AWJ_Billboard::AWJ_Billboard()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);

	planeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	planeMesh->SetupAttachment(rootComp);
	planeMesh->SetRelativeRotation(FRotator(0, 90, 90));
	planeMesh->SetRelativeScale3D(FVector(3, 2, 1));

	playerNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PlayerName"));
	playerNameTxt->SetupAttachment(rootComp);

	//captureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureCamera"));
	//captureCamera->SetupAttachment(rootComp);

	videoPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VideoPlane"));
	videoPlane->SetupAttachment(rootComp);
}

void AWJ_Billboard::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorEnableCollision(false);
	player = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APawn::StaticClass()));
	playerCam = Cast<UCameraComponent>(player->GetDefaultSubobjectByName(TEXT("MainCamera")));

	//playerNameTxt->SetText(TEXT(""));
}

void AWJ_Billboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 위치 회전

	// 마주보게 하기
	/*
	FVector location = GetActorLocation();
	FVector camLocation = playerCam->GetComponentLocation();

	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(location, camLocation);
	rotator.Roll = GetActorRotation().Roll;
	rotator.Yaw += 180;
	SetActorRotation(rotator);
	*/
}

