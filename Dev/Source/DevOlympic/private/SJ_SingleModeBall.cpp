// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SingleModeBall.h"
#include "Components/StaticMeshComponent.h"
#include "SJ_SingleMode.h"
#include "SJ_SinglePingPongPlayer.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASJ_SingleModeBall::ASJ_SingleModeBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	SetRootComponent(ball);

	wrapFX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WrapFX"));
	wrapFX->SetupAttachment(ball);
	wrapFX->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASJ_SingleModeBall::BeginPlay()
{
	Super::BeginPlay();
	
	singleModeBase = Cast<ASJ_SingleMode>(GetWorld()->GetAuthGameMode());

	ball->OnComponentHit.AddDynamic(this, &ASJ_SingleModeBall::OnHit);
}

// Called every frame
void ASJ_SingleModeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_SingleModeBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto player = Cast<ASJ_SinglePingPongPlayer>(OtherActor);

	ball->SetEnableGravity(true);
	wrapFX->SetVisibility(false);

	// ȿ�� ���
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitPointFX, GetActorLocation());

	// ���� ���
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());

	// �̸��˻�
	FString name = OtherActor->GetName();

	if (player && singleModeBase->mode_State == ESingleModeType::Serve)
	{
		singleModeBase->isPlayerHit = true;
	}

	// �ٴڿ� ������ ����
	if (name.Contains("Floor"))
	{
		Destroy();
	}
}

