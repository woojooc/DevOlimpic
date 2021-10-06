// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SingleMode.h"
#include "SJ_SinglePingPongPlayer.h"
#include "SJ_SingleModeBall.h"
#include <Kismet/GameplayStatics.h>

ASJ_SingleMode::ASJ_SingleMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_SingleMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GameModeIn"));
	isPlayerHit  = true;
}

void ASJ_SingleMode::InitGameState()
{
	Super::InitGameState();
}


void ASJ_SingleMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (mode_State)
	{
	case ESingleModeType::Serve:
		ServeMode();
		break;
	case ESingleModeType::Recieve:
		RecieveMode();
		break;
	}
}

void ASJ_SingleMode::ServeMode()
{
	if (isPlayerHit == true)
	{
		currentTime += GetWorld()->DeltaTimeSeconds;

		if (currentTime >= serveModeDelay)
		{
			UE_LOG(LogTemp, Warning, TEXT("BallCreate"));
			ServeModeBallCreate();
		}
		/*GetWorldTimerManager().SetTimer(serveModeTimer, this, &ASJ_SingleMode::ServeModeBallCreate, serveModeDelay);*/
	}
}

void ASJ_SingleMode::RecieveMode()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= recieveModeDelay)
	{
		RecieveBallCreate();
		currentTime = 0;
	}
}

void ASJ_SingleMode::ServeModeBallCreate()
{
	UE_LOG(LogTemp, Warning, TEXT("BallCreate"));
	auto player = Cast<ASJ_SinglePingPongPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_SinglePingPongPlayer::StaticClass()));

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector spawnLoc = player->GetActorLocation();

	ASJ_SingleModeBall* singleBall = nullptr;

	spawnLoc.X = offsetLocA.X;
	spawnLoc.Z = offsetLocA.Z;
	spawnLoc.Y = 60;

	/*if (spawnLoc.Y <= 73)
	{
		spawnLoc.Y = 73;
	}
	else if (spawnLoc.Y >= 73)
	{
		spawnLoc.Y = -73;
	}*/

	singleBall = GetWorld()->SpawnActor<ASJ_SingleModeBall>(pingpongBall, spawnLoc, FRotator::ZeroRotator, Param);
	
	currentTime = 0;
	isPlayerHit = false;
}

void ASJ_SingleMode::RecieveBallCreate()
{
	UE_LOG(LogTemp, Warning, TEXT("ReceieveBallCreate"));
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto player = Cast<ASJ_SinglePingPongPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_SinglePingPongPlayer::StaticClass()));

	FVector spawnLoc = player->GetActorLocation();

	ASJ_SingleModeBall* singleBall = nullptr;

	// y값 랜덤하게 설정 ( -73 ~ 73 )
	int y = FMath::RandRange(-73, 73);

	spawnLoc.X = offsetLocB.X;
	spawnLoc.Y = y;
	spawnLoc.Z = offsetLocB.Z;
	singleBall = GetWorld()->SpawnActor<ASJ_SingleModeBall>(pingpongBall, spawnLoc, FRotator::ZeroRotator, Param);

	singlePingPongBall = singleBall;

	GetWorld()->GetTimerManager().SetTimer(receiveModeTimer, this, &ASJ_SingleMode::AutoServe, 1.0f);
}

void ASJ_SingleMode::AutoServe()
{
	UE_LOG(LogTemp, Warning, TEXT("AutoServe"));
	// 오토 서브
	float x = FMath::RandRange(-50, -128);
	float y = FMath::RandRange(-55, 55);
	float z = FMath::RandRange(95, 140);
	FVector dir = FVector{ x, y, z } - singlePingPongBall->GetActorLocation();
	dir.Normalize();

	float sServePower = FMath::RandRange(1350, 1500);

	// 공에 힘 추가하기
	singlePingPongBall->ball->SetEnableGravity(true);
	singlePingPongBall->ball->AddForce(dir * sServePower);
}
