// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJ_InGameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API USJ_InGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* Btn_Lobby;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* Btn_Quit;

	UFUNCTION()
	void ClickLobby();

	UFUNCTION()
	void ClickQuit();
};
