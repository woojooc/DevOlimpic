// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API AVRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AVRGameModeBase();

	virtual void BeginPlay() override;

	virtual void InitGameState() override;

	virtual void Tick(float DeltaSeconds) override;

	
public:

	// # ¿¢ÅÍ ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere, Category = Components)
	class UWJ_GameStateMgr* gameStateMgr;

	UPROPERTY(EditAnywhere, Category = Components)
	class UWJ_PingPongMgr* pingpongStateMgr;


};
