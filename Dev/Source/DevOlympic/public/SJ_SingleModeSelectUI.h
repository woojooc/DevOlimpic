// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJ_SingleModeSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API USJ_SingleModeSelectUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* Btn_Serve;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* Btn_Receive;

	UFUNCTION()
	void ServeMode();
	UFUNCTION()
	void RecieveMode();
};
