// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_LogUI_Widget.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API USH_LogUI_Widget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* logText;
};
