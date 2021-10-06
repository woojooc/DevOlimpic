// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SJ_SingleMode.generated.h"

UENUM(BlueprintType)
enum class ESingleModeType : uint8
{
	Serve,
	Recieve
};
UCLASS()
class DEVOLYMPIC_API ASJ_SingleMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASJ_SingleMode();

	virtual void BeginPlay() override;
	virtual void InitGameState() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category = SingleMode)
	ESingleModeType mode_State = ESingleModeType::Recieve;

	void ServeMode();
	void RecieveMode();
	void ServeModeBallCreate();
	void RecieveBallCreate();
	void AutoServe();

	// 플레이어 Hit 여부
	UPROPERTY(VisibleAnywhere, Category = SingleMode)
	bool isPlayerHit;

	UPROPERTY(VisibleAnywhere, Category = SingleMode)
	float currentTime;

	FTimerHandle serveModeTimer;
	FTimerHandle receiveModeTimer;
	
	UPROPERTY(EditAnywhere, Category = SingleMode)
	float serveModeDelay = 3.0f;

	UPROPERTY(EditAnywhere, Category = SingleMode)
	float recieveModeDelay = 5.0f;

	UPROPERTY(EditAnywhere, Category = SingleMode)
	TSubclassOf<class ASJ_SingleModeBall> pingpongBall; 

	const FVector offsetLocA = FVector{ -120.f,0.f,126.5f };
	const FVector offsetLocB = FVector{ 120.f,0.f,135.f };

	class ASJ_SingleModeBall* singlePingPongBall;
};
