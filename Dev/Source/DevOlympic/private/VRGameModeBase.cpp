

#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"
#include "WJ_ObjectPool.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_GameOverUI.h"
#include "ModeSelect.h"
#include "WJ_ResultText.h"
#include "WJ_GameInstance.h"


AVRGameModeBase::AVRGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// #Component 생성
	pingpongStateMgr = CreateDefaultSubobject<UWJ_PingPongMgr>(TEXT("PingPongStateManager"));
	objectPool = CreateDefaultSubobject<UWJ_ObjectPool>(TEXT("ObjectPool"));
}

void AVRGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// # 게임모드 설정
	/*
	// 게임모드 셀렉트 월드에서 찾아오기
	modeSelect = Cast<AModeSelect>(UGameplayStatics::GetActorOfClass(GetWorld(), AModeSelect::StaticClass()));
	editMode = modeSelect->m_state;
	*/

	auto gameInstance = Cast<UWJ_GameInstance>(GetGameInstance());
	editMode = gameInstance->modeNum;

	// # 게임 오버 UI 캐싱
	TArray<AActor*> bpGameOverUI;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_GameOverUI::StaticClass(), bpGameOverUI);
	
	if (bpGameOverUI.Num() > 0)
	{
		for (int i = 0; i < bpGameOverUI.Num(); i++)
		{
			AWJ_GameOverUI* emptyPlace = nullptr;
			gameOverUI.Add(emptyPlace);
		}

		for (int i = 0; i < bpGameOverUI.Num(); i++)
		{
			auto ui = Cast<AWJ_GameOverUI>(bpGameOverUI[i]);
			gameOverUI[ui->id] = ui;

			gameOverUI[ui->id]->SetActorHiddenInGame(true);
			gameOverUI[ui->id]->SetActorEnableCollision(false);
		}
	}

	resultText = Cast<AWJ_ResultText>(UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_ResultText::StaticClass()));
	if (resultText)
	{
		resultText->SetActorHiddenInGame(true);
		resultText->SetActorEnableCollision(false);
	}
}

void AVRGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void AVRGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (levelState)
	{
	case EPPLevelState::Intro:
		Intro();
		break;
	case EPPLevelState::PingPong:
		PingPong();
		break;
	case EPPLevelState::GameOver:
		GameOver();
		break;
	default:
		break;
	}
}

// #GET SET
void AVRGameModeBase::SetLevelState(EPPLevelState state)
{
	levelState = state;
}

EPPLevelState AVRGameModeBase::GetLevelState()
{
	return levelState;
}

void AVRGameModeBase::SetWinner(int id)
{
	winner = id;
}

int AVRGameModeBase::GetWinner()
{
	return winner;
}


// #Flow
void AVRGameModeBase::Intro()
{
	if (editMode == EEditMode::Multi)
	{

	}
	else
	{
		SetLevelState(EPPLevelState::PingPong);
	}
}

void AVRGameModeBase::PingPong()
{
	if (isGameStarted)
	{
		return;
	}

	pingpongStateMgr->SetState(EPingPongState::Serv);
	isGameStarted = true;
}

void AVRGameModeBase::GameOver()
{
	if (editMode == EEditMode::Multi)
	{

	}
	else
	{
		gameOverUI[0]->SetActorHiddenInGame(false);
		gameOverUI[0]->SetActorEnableCollision(true);

		resultText->SetActorHiddenInGame(false);

		if (winner == 0)
		{
			resultText->ShowWin();
		}
		else
		{
			resultText->ShowLose();
		}
	}
	
}
