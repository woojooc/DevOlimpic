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
	// 처음엔 공중에 떠있다가 부딪히면 중력 값이 작용하게 하기
	meshComp->SetEnableGravity(true);
	auto sideA = Cast<ASJ_PingPongTableSideA>(OtherActor);
	auto sideB = Cast<ASJ_PingPongTableSideB>(OtherActor);
	auto net = Cast<ASJ_Net>(OtherActor);
	auto player = Cast<ASJ_PingPongPlayer>(OtherActor);

	// 게임 모드 가져오기
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());

	
}

void ASJ_PingPongBall::InitSideState()
{
	inSideA = false;
	inSideB = false;
}

