// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_PPSingleModeWall.h"
#include <Components/StaticMeshComponent.h>
#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"
#include "SJ_PingPongBall.h"

// Sets default values
AWJ_PPSingleModeWall::AWJ_PPSingleModeWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);
	racket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Racket"));
	racket->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWJ_PPSingleModeWall::BeginPlay()
{
	Super::BeginPlay();
	
	racket->OnComponentHit.AddDynamic(this, &AWJ_PPSingleModeWall::OnHit);

	ppball = nullptr;
	auto gameMode = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	ppManager = gameMode->pingpongStateMgr;

}

void AWJ_PPSingleModeWall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ppball = Cast<ASJ_PingPongBall>(OtherActor);

	if (ppball)
	{
		if (ppball->isCallScoreGet == false)
		{
			// 타점 랜덤 선택
			float x = FMath::RandRange(-30, -128);
			float y = FMath::RandRange(-75, 75);
			float z = FMath::RandRange(92, 160);
			FVector dir = FVector{ x, y, z } - ppball->GetActorLocation();
			dir.Normalize();

			ppManager->sServePower = FMath::RandRange(1200, 2200);

			// 공에 힘 추가하기
			ppball->meshComp->SetEnableGravity(true);
			ppball->meshComp->AddForce(dir * ppManager->sServePower);
			ppManager->StartRally();
		}
	}
}

/*
// Called every frame
void AWJ_PPSingleModeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

