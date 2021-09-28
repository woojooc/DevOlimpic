// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_LobbyMenu.h"
#include <Components/WidgetComponent.h>
#include "WJ_ModeSelectUserWidget.h"
#include <Components/Button.h>

// Sets default values
AWJ_LobbyMenu::AWJ_LobbyMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	planeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MenuPlane"));
	planeMesh->SetupAttachment(rootComp);

	planeMesh->SetWorldRotation(FRotator((-90.000000,0,0)));
	planeMesh->SetWorldScale3D(FVector((2.6, 3.8, 1)));

	modeSelectUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ModeSelectUI"));
	modeSelectUI->SetupAttachment(planeMesh);

	mainMenuUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ServerMainMenuUI"));
	mainMenuUI->SetupAttachment(rootComp);
	mainMenuUI->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AWJ_LobbyMenu::BeginPlay()
{
	Super::BeginPlay();
	
	UWJ_ModeSelectUserWidget* modeWidget = Cast<UWJ_ModeSelectUserWidget>(modeSelectUI->GetUserWidgetObject());
	modeWidget->Btn_Multi->OnClicked.AddDynamic(this,&AWJ_LobbyMenu::OpenServerMainMenu);
}

// Called every frame
void AWJ_LobbyMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWJ_LobbyMenu::OpenServerMainMenu()
{
	modeSelectUI->SetHiddenInGame(true);
	planeMesh->SetHiddenInGame(true);
	mainMenuUI->SetHiddenInGame(false);
}

