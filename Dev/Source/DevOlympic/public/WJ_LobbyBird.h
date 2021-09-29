// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_LobbyBird.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_LobbyBird : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_LobbyBird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Paths")
	TArray<AActor*> paths;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float offset = 0.01;

	//int pathIdx = 0;
	int nextIdx = 1;
	FVector center = FVector(123,-774,-38);
};
