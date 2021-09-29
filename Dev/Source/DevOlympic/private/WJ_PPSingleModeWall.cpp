#include "WJ_PPSingleModeWall.h"
#include <Components/StaticMeshComponent.h>
#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"
#include "SJ_PingPongBall.h"

AWJ_PPSingleModeWall::AWJ_PPSingleModeWall()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);
	racket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Racket"));
	racket->SetupAttachment(rootComp);
}

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
			UE_LOG(LogTemp, Warning, TEXT("WALL RECEIVED"));

			// 타점 랜덤 선택
			float x = FMath::RandRange(-50, -128);
			float y = FMath::RandRange(-55, 55);
			float z = FMath::RandRange(110, 160);
			FVector dir = FVector{ x, y, z } - ppball->GetActorLocation();
			dir.Normalize();

			ppManager->sServePower = FMath::RandRange(1500, 2100);

			// 공에 힘 추가하기
			ppball->meshComp->SetEnableGravity(true);
			ppball->meshComp->AddForce(dir * ppManager->sServePower);
		}
	}
}


