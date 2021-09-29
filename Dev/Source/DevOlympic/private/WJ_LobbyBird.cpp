// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_LobbyBird.h"

// Sets default values
AWJ_LobbyBird::AWJ_LobbyBird()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWJ_LobbyBird::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWJ_LobbyBird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (paths.Num() > 0)
	{
		if (nextIdx >= paths.Num())
		{
			nextIdx = 0;
		}
		FVector from = GetActorLocation();
		FVector to = paths[nextIdx]->GetActorLocation();
		FVector loc = FMath::Lerp(from, to, offset);

		float dist = FVector::Dist(from, to);
		if (dist <= 10)
		{
			loc = to;
			//pathIdx++;
			nextIdx++;
			if (nextIdx >= paths.Num())
			{
				//pathIdx = 0;
				nextIdx = 0;
			}
		}

		SetActorLocation(loc);
	}
}

