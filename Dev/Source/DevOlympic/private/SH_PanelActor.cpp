// Fill out your copyright notice in the Description page of Project Settings.


#include "SH_PanelActor.h"
#include <Components/WidgetComponent.h>

// Sets default values
ASH_PanelActor::ASH_PanelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	screenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen Mesh"));
	screenMesh->SetupAttachment(rootComp);
	screenMesh->SetRelativeScale3D(FVector(8.f, 4.5f, 1.f));

	buttonWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Button Widget"));
	buttonWidgetComp->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASH_PanelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASH_PanelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

