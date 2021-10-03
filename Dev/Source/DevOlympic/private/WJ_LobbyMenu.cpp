// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_LobbyMenu.h"
#include <Components/WidgetComponent.h>
#include "WJ_ModeSelectUserWidget.h"
#include <Components/Button.h>
#include "SH_MainMenu.h"

// Sets default values
AWJ_LobbyMenu::AWJ_LobbyMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	planeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MenuPlane"));
	planeMesh->SetupAttachment(rootComp);

	planeMesh->SetWorldRotation(FRotator((-90,0,0)));
	planeMesh->SetWorldScale3D(FVector((2.6, 3.8, 1)));

	planeServerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ServerPlane"));
	planeServerMesh->SetupAttachment(rootComp);
	planeServerMesh->SetWorldRotation(FRotator(-90, 0, 0));
	planeServerMesh->SetWorldScale3D(FVector(1.62, 2.25, 1));

	modeSelectUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ModeSelectUI"));
	modeSelectUI->SetupAttachment(planeMesh);

	mainMenuUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ServerMainMenuUI"));
	mainMenuUI->SetupAttachment(planeServerMesh);
	
	mainMenuUI->SetHiddenInGame(true);
	planeServerMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AWJ_LobbyMenu::BeginPlay()
{
	Super::BeginPlay();
	
	UWJ_ModeSelectUserWidget* modeWidget = Cast<UWJ_ModeSelectUserWidget>(modeSelectUI->GetUserWidgetObject());
	modeWidget->Btn_Multi->OnClicked.AddDynamic(this,&AWJ_LobbyMenu::OpenServerMainMenu);

	USH_MainMenu* serverWidget = Cast<USH_MainMenu>(mainMenuUI->GetUserWidgetObject());
	serverWidget->btn_Quit->OnClicked.AddDynamic(this, &AWJ_LobbyMenu::OpenModeMenu);
}

// Called every frame
void AWJ_LobbyMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWJ_LobbyMenu::OpenServerMainMenu()
{
	planeMesh->SetHiddenInGame(true);
	modeSelectUI->SetHiddenInGame(true);
	planeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	modeSelectUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	planeServerMesh->SetHiddenInGame(false);
	mainMenuUI->SetHiddenInGame(false);
	planeServerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mainMenuUI->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWJ_LobbyMenu::OpenModeMenu()
{
	planeMesh->SetHiddenInGame(false);
	modeSelectUI->SetHiddenInGame(false);
	planeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	modeSelectUI->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	planeServerMesh->SetHiddenInGame(true);
	mainMenuUI->SetHiddenInGame(true);
	planeServerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mainMenuUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

