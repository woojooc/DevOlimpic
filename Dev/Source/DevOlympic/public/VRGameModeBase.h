
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

	// # EditModeSelect		- ��Ƽ || �̱� ����
	class AModeSelect* modeSelect;
	EEditMode editMode;		//ĳ���ؼ� ���

	// # ���� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Components)
		class UWJ_PingPongMgr* pingpongStateMgr;

	UPROPERTY(EditAnywhere, Category = Components)
		class UWJ_ObjectPool* objectPool;

	// # ���� ĳ��
	UPROPERTY(EditAnywhere, Category = UI)
		TArray<class AWJ_GameOverUI*> gameOverUI;	// 0 A, 1 B

	UPROPERTY()
		class AWJ_ResultText* resultText;

	// # ���� ���
	int winner;
	void SetWinner(int id);
	int GetWinner();

	// # ���� �����ߴ��� Ȯ��
	bool isGameStarted = false;


	void Intro();
	void PingPong();
	void GameOver();

};
