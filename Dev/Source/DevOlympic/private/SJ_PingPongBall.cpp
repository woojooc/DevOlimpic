// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PingPongBall.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SJ_PingPongPlayer.h"
#include "SJ_PingPongTableSideA.h"
#include "SJ_PingPongTableSideB.h"
#include "SJ_Net.h"
#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"

// Sets default values
ASJ_PingPongBall::ASJ_PingPongBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	wrapFX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WrapFX"));
	wrapFX->SetupAttachment(meshComp);
	wrapFX->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASJ_PingPongBall::BeginPlay()
{
	Super::BeginPlay();

	meshComp->OnComponentHit.AddDynamic(this, &ASJ_PingPongBall::OnHit);
}

// Called every frame
void ASJ_PingPongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_PingPongBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 처음 생성 될때는 중력이 적용 되어 있지 않고 생성 효과도 나타난다.
	// 따라서 라켓으로 공을 칠때는 중력을 적용 해주고 효과도 꺼준다.
	meshComp->SetEnableGravity(true);
	wrapFX->SetVisibility(false);

	auto sideA = Cast<ASJ_PingPongTableSideA>(OtherActor);
	auto sideB = Cast<ASJ_PingPongTableSideB>(OtherActor);
	auto net = Cast<ASJ_Net>(OtherActor);
	auto player = Cast<ASJ_PingPongPlayer>(OtherActor);

	// 게임 모드 가져오기
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());

	// 이름검사
	FString name = OtherActor->GetName();

	// 플레이어 SideA 에 부딪혔을 때
	if (sideA)
	{
		// SideA 에 처음 충돌 했을 때
		if (inSideA == false)
		{
			inSideA = true;
		}
		// 동일사이드 중복 충돌 시 실점(true 일 때 또 충돌)
		else if (inSideA == true)
		{
			if (isOnGround == false)
			{
				vrGameMNG->pingpongStateMgr->OnCollisionGround(playerID, false);
				InitSideState();
				isOnGround = true;
			}
		}

		// 사운드 재생
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// 플레이어 SideB 에 부딪혔을 때
	else if (sideB)
	{
		// SideA와 동일하게
		if (inSideB == false)
		{
			inSideB = true;
		}
		else if (inSideB == true)
		{
			if (isOnGround == false)
			{
				vrGameMNG->pingpongStateMgr->OnCollisionGround(playerID, false);
				// 초기화 함수
				InitSideState();
				isOnGround = true;
			}
		}

		// 사운드 재생
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// 네트에 부딪혔을때
	else if (net)
	{
		
		//vrGameMNG->pingpongStateMgr->NetServ();
	}
	// 플레이어가 쳤을 때
	else if (player)
	{
		// 랠리 시작
		vrGameMNG->pingpongStateMgr->StartRally();

		// 플레이어 A 가 쳤을때
		playerID = 0;

		// 사운드 재생
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// 장외로 되서 바닥에 부딪혔을때
	else if (name.Contains("Floor"))
	{
		// A, B 둘 다 충돌 후 그라운드시 득점
		if (inSideA == true && inSideB == true)
		{
			if (isOnGround == false)
			{
				vrGameMNG->pingpongStateMgr->OnCollisionGround(playerID, true);
				isOnGround = true;
			}
		}
		else
		{
			if (isOnGround == false)
			{
				vrGameMNG->pingpongStateMgr->OnCollisionGround(playerID, false);
				isOnGround = true;
			}
		}
		// 초기화 함수
		InitSideState();
	}

}

void ASJ_PingPongBall::InitSideState()
{
	inSideA = false;
	inSideB = false;
	playerID = -1;
}

