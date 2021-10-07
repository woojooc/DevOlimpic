// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_SingleModeSelectUIPannel.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_SingleModeSelectUIPannel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_SingleModeSelectUIPannel();

	UPROPERTY(EditAnywhere, Category = UIComponent)
	class USceneComponent* rootComp;
	UPROPERTY(EditAnywhere, Category = UIComponent)
	class UStaticMeshComponent* planeMesh;
	UPROPERTY(EditAnywhere, Category = UIComponent)
	class UWidgetComponent* selectUI;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowUI();
	void HideUI();

	UPROPERTY(VisibleAnywhere, Category = Visible)
	bool isActive;

	bool bOpen = false;
	bool bClose = false;

	FVector maxScale;
	FVector minScale;

};
