// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_Billboard.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_Billboard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_Billboard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Root")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "Billboard")
	class UStaticMeshComponent* planeMesh;
	UPROPERTY(EditAnywhere, Category = "Billboard")
	class UTextRenderComponent* playerNameTxt;

	UPROPERTY(EditAnywhere, Category = "Billboard")
	class USceneCaptureComponent2D* captureCamera;
	UPROPERTY(EditAnywhere, Category = "Billboard")
	class UStaticMeshComponent* videoPlane;


	UPROPERTY()
	class APawn* player;
	UPROPERTY()
	class UCameraComponent* playerCam;

	UPROPERTY(EditAnywhere,Category = "Player")
	int playerID;

};
