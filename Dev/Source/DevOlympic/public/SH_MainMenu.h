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


	// ���� ȣ��Ʈ �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void HostGame();

	// ���� ���� �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void JoinGame();

	// ���� ���� �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void QuitGame();

};
