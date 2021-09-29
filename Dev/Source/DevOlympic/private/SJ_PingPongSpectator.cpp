// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PingPongSpectator.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASJ_PingPongSpectator::ASJ_PingPongSpectator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(capComp);
	capComp->SetCapsuleHalfHeight(65.0f);
	capComp->SetCapsuleRadius(40.0f);

	root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	root->SetupAttachment(RootComponent);

	face = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face"));
	face->SetupAttachment(root);

	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	body->SetupAttachment(root);

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	rightHand->SetupAttachment(root);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	leftHand->SetupAttachment(root);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));
}

// Called when the game starts or when spawned
void ASJ_PingPongSpectator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASJ_PingPongSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASJ_PingPongSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASJ_PingPongSpectator::JumpUp()
{
	FVector me = GetActorLocation();
	FVector upVector = root->GetUpVector();
	// 위로 이동 했다가 다시 내려온다
	FVector ss = FMath::Lerp(me, me + upVector * 100.0f , 3.0f);
	SetActorLocation(ss);

}

