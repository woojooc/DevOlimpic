// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_SingleModeSelectUIPannel.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_SingleModeSelectUIPannel::ASJ_SingleModeSelectUIPannel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	planeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	planeMesh->SetupAttachment(rootComp);
	planeMesh->SetWorldRotation(FRotator(-90, 0, 0));
	planeMesh->SetWorldScale3D(FVector(1.5, 2.8, 1));

	selectUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ShowUI"));
	selectUI->SetupAttachment(planeMesh);

}

// Called when the game starts or when spawned
void ASJ_SingleModeSelectUIPannel::BeginPlay()
{
	Super::BeginPlay();
	planeMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	HideUI();

	maxScale = GetActorScale3D();
	minScale = maxScale * 0.3;
	SetActorScale3D(minScale);
}

// Called every frame
void ASJ_SingleModeSelectUIPannel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpen)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Open"));
		ShowUI();
	}

	if (bClose)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Close"));
		HideUI();
	}
}

void ASJ_SingleModeSelectUIPannel::ShowUI()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetOpen();
	bOpen = true;
	bClose = false;
	
	isActive = true;
}

void ASJ_SingleModeSelectUIPannel::HideUI()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetClose();
	bOpen = false;
	bClose = true;

	isActive = false;
}

void ASJ_SingleModeSelectUIPannel::SetOpen()
{
	bOpen = true;
}

void ASJ_SingleModeSelectUIPannel::SetClose()
{
	bClose = true;
}

void ASJ_SingleModeSelectUIPannel::Open()
{
	FVector curScale = GetActorScale3D();
	FVector scale = FMath::Lerp(curScale, maxScale, 0.1);

	float dist = FVector::Dist(scale, maxScale);
	if (dist < 0.5)
	{
		scale = maxScale;
		bOpen = false;
	}
	SetActorScale3D(scale);
}

void ASJ_SingleModeSelectUIPannel::Close()
{
	FVector curScale = GetActorScale3D();
	FVector scale = FMath::Lerp(curScale, minScale, 0.1);

	float dist = FVector::Dist(scale, minScale);
	if (dist < 0.5)
	{
		scale = minScale;
		bClose = false;

		// 다 작아지면 SetHidden true
		SetActorHiddenInGame(true);
	}
	SetActorScale3D(scale);
}

