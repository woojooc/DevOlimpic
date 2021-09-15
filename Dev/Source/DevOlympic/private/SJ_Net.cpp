// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Net.h"
#include "Components/BoxComponent.h"

// Sets default values
ASJ_Net::ASJ_Net()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	net = CreateDefaultSubobject<UBoxComponent>(TEXT("Net"));
	SetRootComponent(net);
}

// Called when the game starts or when spawned
void ASJ_Net::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASJ_Net::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

