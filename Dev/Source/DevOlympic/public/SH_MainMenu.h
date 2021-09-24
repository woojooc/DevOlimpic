// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_MainMenu.generated.h"

/**
 *
 */
UCLASS()
class DEVOLYMPIC_API USH_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Host;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Join;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Quit;


	// 게임 호스트 함수
	UFUNCTION(BlueprintImplementableEvent)
		void HostGame();

	// 게임 조인 함수
	UFUNCTION(BlueprintImplementableEvent)
		void JoinGame();

	// 게임 종료 함수
	UFUNCTION(BlueprintImplementableEvent)
		void QuitGame();

};
