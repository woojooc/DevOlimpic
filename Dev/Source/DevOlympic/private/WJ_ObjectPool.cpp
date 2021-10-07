

#include "WJ_ObjectPool.h"
#include "SJ_PingPongBall.h"
#include "Net/UnrealNetwork.h"

UWJ_ObjectPool::UWJ_ObjectPool()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWJ_ObjectPool::BeginPlay()
{
	Super::BeginPlay();

	double secs = FTimespan(FDateTime::Now().GetTicks()).GetTotalSeconds();
	int32 seed = (int32)(((int64)secs) % INT_MAX);
	FMath::RandInit(seed);
}


void UWJ_ObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

ASJ_PingPongBall* UWJ_ObjectPool::GetPingPongBall(AActor* actor, int player, EEditMode mode)
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FVector spawnLoc = actor->GetActorLocation();

	ASJ_PingPongBall* ppBall = nullptr;

	if (mode == EEditMode::Multi)
	{
		if (player == 0)
		{
			//UE_LOG(LogTemp,Warning,TEXT("GetPingPongBall Player 0"));
			spawnLoc.X = offsetLocA.X;
			spawnLoc.Z = offsetLocA.Z;

			// y값 제한
			if (spawnLoc.Y <= -73)
			{
				spawnLoc.Y = -73;
			}
			else if (spawnLoc.Y >= 73)
			{
				spawnLoc.Y = 73;
			}

			if(GetWorld()->GetGameState()->HasAuthority())
			ppBall = GetWorld()->SpawnActor<ASJ_PingPongBall>(pingpongFactory, spawnLoc, FRotator::ZeroRotator, Param);
		}
		else
		{
			spawnLoc.X = offsetLocB.X;
			spawnLoc.Z = offsetLocA.Z;

			// y값 제한
			if (spawnLoc.Y <= -73)
			{
				spawnLoc.Y = -73;
			}
			else if (spawnLoc.Y >= 73)
			{
				spawnLoc.Y = 73;
			}

			if (GetWorld()->GetGameState()->HasAuthority())
			ppBall = GetWorld()->SpawnActor<ASJ_PingPongBall>(pingpongFactory, spawnLoc, FRotator::ZeroRotator, Param);
		}
	}
	else
	{
		if (player == 0)
		{
			//UE_LOG(LogTemp,Warning,TEXT("GetPingPongBall Player 0"));
			spawnLoc.X = offsetLocA.X;
			spawnLoc.Z = offsetLocA.Z;

			// y값 제한
			if (spawnLoc.Y <= -73)
			{
				spawnLoc.Y = -73;
			}
			else if (spawnLoc.Y >= 73)
			{
				spawnLoc.Y = 73;
			}

			ppBall = GetWorld()->SpawnActor<ASJ_PingPongBall>(pingpongFactory, spawnLoc, FRotator::ZeroRotator, Param);
		}
		else
		{
			// y값 랜덤하게 설정 ( -73 ~ 73 )
			int y = FMath::RandRange(-73, 73);

			spawnLoc.X = offsetLocB.X;
			spawnLoc.Y = y;
			spawnLoc.Z = offsetLocB.Z;
			ppBall = GetWorld()->SpawnActor<ASJ_PingPongBall>(pingpongFactory, spawnLoc, FRotator::ZeroRotator, Param);
		}
	}

	return ppBall;
}
