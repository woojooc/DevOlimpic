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
	
	randomFirstTime = FMath::RandRange(2.0f, 5.0f);
	
	IdlePos = GetActorLocation();

	GetWorldTimerManager().SetTimer(firstJumpTimer, this, &ASJ_PingPongSpectator::JumpUp, randomFirstTime);
}

// Called every frame
void ASJ_PingPongSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (j_State)
	{
	case EJumpState::Idle:
		Idle();
		break;
	case EJumpState::Jump:
		Jump();
		break;
	case EJumpState::Down:
		Down();
		break;
	}
}

// Called to bind functionality to input
void ASJ_PingPongSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASJ_PingPongSpectator::Idle()
{
	
}

void ASJ_PingPongSpectator::Jump()
{
	FVector myPos = GetActorLocation();

	jumpPos = GetActorLocation() + FVector::UpVector * jumpPower;

	myPos = FMath::Lerp(myPos, jumpPos, GetWorld()->DeltaTimeSeconds * 0.3f);

	float distance = FVector::Dist(IdlePos, myPos);

	if (distance >100.0f)
	{
		j_State = EJumpState::Down;
	}

	SetActorLocation(myPos);
}

void ASJ_PingPongSpectator::Down()
{
	FVector myPos = GetActorLocation();

	downPos = GetActorLocation() + FVector::DownVector * jumpPower;

	myPos = FMath::Lerp(myPos, downPos, GetWorld()->DeltaTimeSeconds * 0.5f);

	float distance = FVector::Dist(IdlePos, myPos);

	if (distance < 10.0f)
	{
		randomTime = FMath::RandRange(10.0f, 20.0f);
		GetWorldTimerManager().SetTimer(jumpTimer, this, &ASJ_PingPongSpectator::JumpUp, randomTime);

		j_State = EJumpState::Idle;
	}

	SetActorLocation(myPos);
}

void ASJ_PingPongSpectator::JumpUp()
{
	j_State = EJumpState::Jump;
}

