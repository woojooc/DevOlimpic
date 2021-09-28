// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WJ_ModeSelectUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API UWJ_ModeSelectUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Buttons", meta = (BindWidget))
	class UButton* Btn_Single;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Buttons", meta = (BindWidget))
	class UButton* Btn_Multi;

	UFUNCTION()
	void ClickSingle();
	UFUNCTION()
	void ClickMulti();

};
