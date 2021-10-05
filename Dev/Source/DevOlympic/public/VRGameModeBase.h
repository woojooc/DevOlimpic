
#pragma once

#include "DevOlympic.h"
#include "GameFramework/GameStateBase.h"
#include "VRGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class DEVOLYMPIC_API AVRGameModeBase : public AGameStateBase
{
	GENERATED_BODY()

public:

	AVRGameModeBase();

	virtual void BeginPlay() override;

	//virtual void InitGameState() override;

	virtual void Tick(float DeltaSeconds) override;


public:

	// # Level Flow Enum
	EPPLevelState levelState;
	void SetLevelState(EPPLevelState state);
	EPPLevelState GetLevelState();

	// # EditModeSelect		- 멀티 || 싱글 선택
	class AModeSelect* modeSelect;
	EEditMode editMode;		//캐싱해서 사용

	// # 엑터 컴포넌트
	UPROPERTY(EditAnywhere, Category = Components)
		class UWJ_PingPongMgr* pingpongStateMgr;

	UPROPERTY(EditAnywhere, Category = Components)
		class UWJ_ObjectPool* objectPool;

	// # 엑터 캐싱
	UPROPERTY(EditAnywhere, Category = UI)
		TArray<class AWJ_GameOverUI*> gameOverUI;	// 0 A, 1 B

	UPROPERTY()
		class AWJ_ResultText* resultText;

	// # 게임 결과
	int winner;
	void SetWinner(int id);
	int GetWinner();

	// # 게임 시작했는지 확인
	bool isGameStarted = false;


	void Intro();
	void PingPong();
	void GameOver();

};
