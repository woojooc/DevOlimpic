

#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"
#include "WJ_ObjectPool.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_GameOverUI.h"
#include "ModeSelect.h"


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
	// 게임모드 셀렉트 월드에서 찾아오기
	modeSelect = Cast<AModeSelect>(UGameplayStatics::GetActorOfClass(GetWorld(), AModeSelect::StaticClass()));
	editMode = modeSelect->m_state;

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
		}
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

void AVRGameModeBase::SetLevelState(EPPLevelState state)
{
	levelState = state;
}

EPPLevelState AVRGameModeBase::GetLevelState()
{
	return levelState;
}

void AVRGameModeBase::Intro()
{
	SetLevelState(EPPLevelState::PingPong);
}

void AVRGameModeBase::PingPong()
{
	pingpongStateMgr->SetState(EPingPongState::Serv);
}

void AVRGameModeBase::GameOver()
{
	for (int i = 0; i < 2; i++)
	{
		if (gameOverUI[i]->id == 0)
		{
			gameOverUI[i]->SetActorHiddenInGame(false);
		}
	}
	
}
