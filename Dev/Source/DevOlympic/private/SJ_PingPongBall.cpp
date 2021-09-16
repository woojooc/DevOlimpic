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

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
}

void ASJ_PingPongBall::InitSideState()
{
	inSideA = false;
	inSideB = false;
}

