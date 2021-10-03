// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_GameOverUI.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_GameOverUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_GameOverUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void HideUI();
	void Show();


	// # 
	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* rootComp;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* planeMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UWidgetComponent* menuUI;

	UPROPERTY(EditAnywhere, Category = "Settings")
	int id;

	UPROPERTY(VisibleAnywhere, Category = Visible)
	bool isActive;
};
