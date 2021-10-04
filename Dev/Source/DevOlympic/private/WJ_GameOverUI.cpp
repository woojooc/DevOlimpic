// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_GameOverUI.h"
#include <Components/WidgetComponent.h>

// Sets default values
AWJ_GameOverUI::AWJ_GameOverUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	planeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	planeMesh->SetupAttachment(rootComp);
	planeMesh->SetWorldRotation(FRotator(-90, 0, 0));
	planeMesh->SetWorldScale3D(FVector(1.5, 2.8, 1));

	menuUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("MenuUI"));
	menuUI->SetupAttachment(planeMesh);
}

// Called when the game starts or when spawned
void AWJ_GameOverUI::BeginPlay()
{
	Super::BeginPlay();
	
	isActive = false;
}

void AWJ_GameOverUI::HideUI()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	/*
	menuUI->SetHiddenInGame(true);
	menuUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	planeMesh->SetHiddenInGame(true);
	planeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	*/
	
	isActive = false;
}

void AWJ_GameOverUI::Show()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	/*
	menuUI->SetHiddenInGame(false);
	menuUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	planeMesh->SetHiddenInGame(false);
	planeMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	*/
	
	isActive = true;
}

