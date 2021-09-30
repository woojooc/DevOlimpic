// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_ResultText.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_ResultText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_ResultText();

	void ShowWin();
	void ShowLose();
	void HidQeAll();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Root")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "TEXT")
		class USceneComponent* winText;
	UPROPERTY(EditAnywhere, Category = "TEXT")
		class USceneComponent* loseText;

	UPROPERTY(EditAnywhere, Category = "TEXT")
	TArray<UStaticMeshComponent*> winTexts;
	UPROPERTY(EditAnywhere, Category = "TEXT")
	TArray<UStaticMeshComponent*> loseTexts;
};
