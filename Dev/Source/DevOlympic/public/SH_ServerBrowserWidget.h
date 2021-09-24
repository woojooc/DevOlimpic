// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_ServerBrowserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API USH_ServerBrowserWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Join;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Refresh;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Back;


	// 게임 호스트 함수
	UFUNCTION(BlueprintImplementableEvent)
		void JoinGame();

	// 게임 조인 함수
	UFUNCTION(BlueprintImplementableEvent)
		void RefreshServerList();

	// 게임 종료 함수
	UFUNCTION(BlueprintImplementableEvent)
		void BackToMainMenu();
};
