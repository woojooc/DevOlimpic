// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_OutOfZone.h"
#include "Components/BoxComponent.h"

// Sets default values
ASJ_OutOfZone::ASJ_OutOfZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	zone = CreateDefaultSubobject<UBoxComponent>(TEXT("OutOfZone"));
	SetRootComponent(zone);
}

// Called when the game starts or when spawned
void ASJ_OutOfZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASJ_OutOfZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

