

#include "WJ_ObjectPool.h"
#include "SJ_PingPongBall.h"

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

void UWJ_ObjectPool::GetPingPongBall(AActor* actor, int player, EEditMode mode)
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FVector spawnLoc = actor->GetActorLocation();

	if (mode == EEditMode::Multi)
	{

	}
	else
	{
		if (player == 0)
		{
			UE_LOG(LogTemp,Warning,TEXT("GetPingPongBall Player 0"));
			spawnLoc.X = offsetLocA.X;
			spawnLoc.Z = offsetLocA.Z;
			auto ppBall = GetWorld()->SpawnActor<ASJ_PingPongBall>(pingpoingFactory, spawnLoc, FRotator::ZeroRotator, Param);
		}
		else
		{
			// y값 랜덤하게 설정 ( -74 ~ 73 )
			int y = FMath::RandRange(-74, 73);

			spawnLoc.X = offsetLocB.X;
			spawnLoc.Y = y;
			spawnLoc.Z = offsetLocB.Z;
			auto ppBall = GetWorld()->SpawnActor<ASJ_PingPongBall>(pingpoingFactory, spawnLoc, FRotator::ZeroRotator, Param);
		}
	}
}
