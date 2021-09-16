

#include "WJ_Point.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h"

AWJ_Point::AWJ_Point()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	pointA = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Point A"));
	pointA->SetupAttachment(rootComp);
	pointA->SetWorldSize(20);
	pointA->SetHorizontalAlignment(EHTA_Center);
	pointA->SetVerticalAlignment(EVRTA_TextCenter);
	pointA->SetVerticalAlignment(EVRTA_TextCenter);
	pointA->SetText(FText::FromString("00"));


	middle = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Middle"));
	middle->SetupAttachment(rootComp);
	middle->SetWorldSize(20);
	middle->SetHorizontalAlignment(EHTA_Center);
	middle->SetVerticalAlignment(EVRTA_TextCenter);
	middle->SetText(FText::FromString(":"));

	pointB = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Point B"));
	pointB->SetupAttachment(rootComp);
	pointB->SetWorldSize(20);
	pointB->SetHorizontalAlignment(EHTA_Center);
	pointB->SetVerticalAlignment(EVRTA_TextCenter);
	pointB->SetText(FText::FromString("00"));

}

void AWJ_Point::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
void AWJ_Point::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

void AWJ_Point::SetPoint(int player, int point)
{
	FString p = FString::Printf(TEXT("%0d"),point);
	if (player == 0)
	{
		pointA->SetText(FText::FromString(p));
	}
	else
	{
		pointB->SetText(FText::FromString(p));
	}
}

void AWJ_Point::ResetPoint()
{
	pointA->SetText(FText::FromString("00"));
	pointB->SetText(FText::FromString("00"));
}

void AWJ_Point::SetColor(FColor color)
{
	pointA->SetTextRenderColor(color);
	middle->SetTextRenderColor(color);
	pointB->SetTextRenderColor(color);
}

