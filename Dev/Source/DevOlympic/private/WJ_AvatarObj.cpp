

#include "WJ_AvatarObj.h"

// Sets default values
AWJ_AvatarObj::AWJ_AvatarObj()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	bodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyComp"));
	bodyComp->SetupAttachment(rootComp);
	bodyComp->SetSimulatePhysics(true);
	bodyComp->SetEnableGravity(true);
	bodyComp->SetCollisionProfileName(TEXT("Avatar"));


	headComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadComp"));
	headComp->SetupAttachment(bodyComp);
}

void AWJ_AvatarObj::BeginPlay()
{
	Super::BeginPlay();
	
}

