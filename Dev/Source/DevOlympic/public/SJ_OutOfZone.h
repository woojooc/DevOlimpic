// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_OutOfZone.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_OutOfZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_OutOfZone();

	UPROPERTY(VisibleAnywhere, Category = OutOfZone)
	class UBoxComponent* zone;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
