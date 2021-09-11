// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DevOlympic.h"
#include "Components/ActorComponent.h"
#include "WJ_GameStateMgr.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API UWJ_GameStateMgr : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWJ_GameStateMgr();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetState(EGameState state);
	EGameState GetState();

private:
	EGameState m_state = EGameState::Lobby;

};
