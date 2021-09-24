// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SH_PanelActor.generated.h"

UCLASS()
class DEVOLYMPIC_API ASH_PanelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASH_PanelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
		class UStaticMeshComponent* screenMesh;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
		class UWidgetComponent* buttonWidgetComp;

};
