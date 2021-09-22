// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SH_LobbyHandAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API USH_LobbyHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSettings)
	float gripValue;
};
