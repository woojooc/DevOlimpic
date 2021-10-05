

#include "WJ_AvatarObj.h"
#include <Components/CapsuleComponent.h>
#include <Components/TextRenderComponent.h>

// Sets default values
AWJ_AvatarObj::AWJ_AvatarObj()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collsion"));
	collision->SetupAttachment(rootComp);
	collision->SetSimulatePhysics(false);
	collision->SetEnableGravity(false);
	collision->SetCollisionProfileName(TEXT("Avatar"));

	bodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyComp"));
	bodyComp->SetupAttachment(collision);

	headComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadComp"));
	headComp->SetupAttachment(collision);

	arrowTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ArrowText"));
	arrowTxt->SetupAttachment(rootComp);
	selectTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("SelectText"));
	selectTxt->SetupAttachment(rootComp);
}

void AWJ_AvatarObj::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWJ_AvatarObj::HideText()
{
	arrowTxt->SetVisibility(false);
	selectTxt->SetVisibility(false);
}

