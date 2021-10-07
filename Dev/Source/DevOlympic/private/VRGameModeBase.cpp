

#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"
#include "WJ_ObjectPool.h"
#include <Kismet/GameplayStatics.h>
#include "WJ_GameOverUI.h"
#include "ModeSelect.h"
#include "WJ_ResultText.h"
#include "WJ_GameInstance.h"
#include "WJ_Billboard.h"
#include <Components/TextRenderComponent.h>
#include "SJ_PingPongPlayer.h"


AVRGameModeBase::AVRGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// #Component ����
	pingpongStateMgr = CreateDefaultSubobject<UWJ_PingPongMgr>(TEXT("PingPongStateManager"));
	objectPool = CreateDefaultSubobject<UWJ_ObjectPool>(TEXT("ObjectPool"));
	// �Ŵ��� ������Ʈ ����ȭ 
	pingPongMgrRepComponent = CreateDefaultSubobject<USH_PingPongMgrRepComponent>(TEXT("PingPongMgrRepComponent"));
}

void AVRGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("GameModeBase BeginPlay"));

	// # ���Ӹ�� ����
	/*
	// ���Ӹ�� ����Ʈ ���忡�� ã�ƿ���
	modeSelect = Cast<AModeSelect>(UGameplayStatics::GetActorOfClass(GetWorld(), AModeSelect::StaticClass()));
	editMode = modeSelect->m_state;
	*/

	auto gameInstance = Cast<UWJ_GameInstance>(GetWorld()->GetGameInstance());
	editMode = gameInstance->modeNum;

	//UE_LOG(LogTemp,Warning,TEXT("gameInstance : %d"), gameInstance->modeNum);
	//UE_LOG(LogTemp,Warning,TEXT("editMode : %d"),editMode);

	// # ���� ���� UI ĳ��
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

	// ��� �ؽ�Ʈ ������Ʈ ĳ��
	resultText = Cast<AWJ_ResultText>(UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_ResultText::StaticClass()));
	if (resultText)
	{
		resultText->SetActorHiddenInGame(true);
		resultText->SetActorEnableCollision(false);
	}

	// ������ ĳ��
	TArray<AActor*> billboardObjs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_Billboard::StaticClass(), billboardObjs);

	if (billboardObjs.Num() > 0)
	{
		for (int i = 0; i < billboardObjs.Num(); i++)
		{
			AWJ_Billboard* emptyObj;
			billObjs.Add(emptyObj);
		}

		for (int i = 0; i < billboardObjs.Num(); i++)
		{
			auto obj = Cast<AWJ_Billboard>(billboardObjs[i]);
			billObjs[obj->playerID] = obj;
		}
	}

	if (editMode == EEditMode::Multi)
	{
		if (HasAuthority())
		{
			billObjs[0]->playerNameTxt->SetText(FText::FromString(TEXT("A")));
		}
		else
		{
			billObjs[1]->playerNameTxt->SetText(FText::FromString(TEXT("B")));
		}
	}
	else
	{
		billObjs[0]->playerNameTxt->SetText(FText::FromString(TEXT("A")));
		billObjs[1]->SetActorHiddenInGame(true);
	}
}

//void AVRGameModeBase::InitGameState()
//{
//	Super::InitGameState();
//}

void AVRGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (levelState)
	{
	case EPPLevelState::Intro:
		Intro();
		break;
	case EPPLevelState::Setting:
		Setting();
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

void AVRGameModeBase::Setting()
{
	TArray<AActor*> players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASJ_PingPongPlayer::StaticClass(), players);
	if (players.Num() > 0)
	{
		for (int i = 0; i < players.Num(); i++)
		{
			if (Cast<ASJ_PingPongPlayer>(players[i])->playerIndex == 0)
			{
				pingpongStateMgr->playerActorA = players[i];
				// �÷��̾� ���̵� �޾ƿͼ� �����ϱ�.
			}
			else
			{
				pingpongStateMgr->playerActorB = players[i];
			}
		}
	}

	SetLevelState(EPPLevelState::PingPong);
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
