
#pragma once

#include "DevOlympic.h"
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
	
	// # Level Flow Enum
	EPPLevelState levelState;
	void SetLevelState(EPPLevelState state);
	EPPLevelState GetLevelState();

	// # EditModeSelect		- ¸ÖÆ¼ || ½Ì±Û ¼±ÅÃ
	class AModeSelect* modeSelect;
	EEditMode editMode;		//Ä³½ÌÇØ¼­ »ç¿ë

	// # ¿¢ÅÍ ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere, Category = Components)
	class UWJ_PingPongMgr* pingpongStateMgr;

	UPROPERTY(EditAnywhere, Category = Components)
	class UWJ_ObjectPool* objectPool;

	UPROPERTY()
	TArray<class AWJ_GameOverUI*> gameOverUI;	// 0 A, 1 B

	void Intro();
	void PingPong();
	void GameOver();

};
