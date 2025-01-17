// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_LobbyMenu.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_LobbyMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_LobbyMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* rootComp;

	// # Mode
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* planeMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UWidgetComponent* modeSelectUI;

	// # ServerMain
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* planeServerMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UWidgetComponent* mainMenuUI;

	UFUNCTION()
	void OpenServerMainMenu();
	UFUNCTION()
	void OpenModeMenu();

	// ���
	bool bOpen = false;
	bool bClose = false;
	void SetOpen();
	void SetClose();

	void Open();
	void Close();

	FVector maxScale;
	FVector minScale;
};
