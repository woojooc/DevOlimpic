// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DevOlympic.h"
#include "GameFramework/Actor.h"
#include "WJ_TutorialObj.generated.h"



UCLASS()
class DEVOLYMPIC_API AWJ_TutorialObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_TutorialObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category = "Category")
	ETutoUIType tutoType;

	UPROPERTY(EditAnywhere, Category = "Eyetrace")
	bool bCanEyeTrace = false;

	UPROPERTY()
	class AWJ_LobbyPlayer* player;
	UPROPERTY()
	class UCameraComponent* playerCam;
};
