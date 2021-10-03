

#include "WJ_AvatarObj.h"
#include <Components/CapsuleComponent.h>

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
}

void AWJ_AvatarObj::BeginPlay()
{
	Super::BeginPlay();
	
}

