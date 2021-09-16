

#include "WJ_PingPongMgr.h"
#include "VRGameModeBase.h"
#include "WJ_ObjectPool.h"
#include "Kismet/GameplayStatics.h"
#include "ModeSelect.h"
#include "WJ_PPSingleModeWall.h"
#include "WJ_Point.h"
#include "PingPongPlayer.h"


UWJ_PingPongMgr::UWJ_PingPongMgr()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWJ_PingPongMgr::BeginPlay()
{
	Super::BeginPlay();

	//gameModeBase ĳ��
	gameModeBase = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());

	// # ���Ӹ�� ����
	// ���Ӹ�� ����Ʈ ���忡�� ã�ƿ���
	modeSelect = Cast<AModeSelect>(UGameplayStatics::GetActorOfClass(GetWorld(), AModeSelect::StaticClass()));
	editMode = modeSelect->m_state;

	// # ������ ĳ��
	TArray<AActor*> bpPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_Point::StaticClass(),bpPoints);
	//pointPannel = Cast<AWJ_Point>(UGameplayStatics::GetActorOfClass(GetWorld(),AWJ_Point::StaticClass()));
	if (bpPoints.Num() != 0)
	{
		pointPannel = Cast<AWJ_Point>(bpPoints[0]);
		pointPannel->SetColor(FColor::Blue);
		scorePannel = Cast<AWJ_Point>(bpPoints[1]);
		scorePannel->SetColor(FColor::Red);
	}

	playerActorA = UGameplayStatics::GetActorOfClass(GetWorld(),APingPongPlayer::StaticClass());
	if (editMode == EEditMode::Multi)
	{
		// �÷��̾� ȣ��Ʈ ( 0, A ) -> Ź���� ���̵� A
		// �÷��̾� �Խ�Ʈ ( 1, B ) -> Ź���� ���̵� B �� ��ȯ

		// ù ���� �������� �̱�
	}
	else
	{
		playerActorB = UGameplayStatics::GetActorOfClass(GetWorld(),AWJ_PPSingleModeWall::StaticClass());

		// �� Ȱ��ȭ
		AActor* wall = UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_PPSingleModeWall::StaticClass());
		if (wall)
		{
			wall->SetActorHiddenInGame(false);
		}

		// ���� ����
		bServPlayer = 0;
	}
}


void UWJ_PingPongMgr::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (m_state)
	{
	case EPingPongState::Intro:
		// ���
		Intro();
		break;

	case EPingPongState::Serv:
		// �� ��ȯ
		Serv();
		break;

	case EPingPongState::Rally:
		// �浹 üũ
		//Rally();
		break;

	case EPingPongState::RallyOver:
		// �� ����
		// ����(point) ȹ��
		// 10 : 10 ==> Serv, bIsDeuse = true : 2������������ �ݺ�
		// point < 11 ==> Serv
		// 11 ==> SetOver
		//RallyOver();
		break;

	case EPingPongState::SetOver:
		// set < 5  ==>  Serv
		// 5 ==> MatchOver
		SetOver();
		break;

	case EPingPongState::MatchOver:
		// score �� ���� ����
		MatchOver();
		break;

	default:
		break;
	}
}

void UWJ_PingPongMgr::Intro()
{
	SetState(EPingPongState::Serv);
}

void UWJ_PingPongMgr::Serv()
{
	// ���� �����Ǿ����� ���
	if (bSpawnBall)
	{
		return;
	}

	// bServPlayer�� T -> A ��ġ�� �� ����
	// else -> B ��ġ�� �� ����
	if (bServPlayer == 0)
	{
		//A �� ����
		if (playerActorA)
		{
			gameModeBase->objectPool->GetPingPongBall(playerActorA,0,editMode);
			bSpawnBall = true;
		}
	}
	else
	{
		//B �� ����
		gameModeBase->objectPool->GetPingPongBall(playerActorB,1,editMode);
		bSpawnBall = true;
	}

	// �÷��̾ ���� ġ�� �̺�Ʈ �߻�
}

void UWJ_PingPongMgr::Rally()
{
	
}

void UWJ_PingPongMgr::RallyOver()
{

}

void UWJ_PingPongMgr::SetOver()
{
	set++;
	pointA = 0;
	pointB = 0;
	pointPannel->ResetPoint();

	if (set == 5)
	{
		SetState(EPingPongState::MatchOver);
		return;
	}

	SetState(EPingPongState::Serv);
}

void UWJ_PingPongMgr::MatchOver()
{
	if (scoreA > scoreB)
	{
		// A �¸�
	}
	else
	{
		// B �¸�
	}

	// ���� ���� �κ�� ���ư��� ��ư ������Ʈ Ȱ��ȭ
}

void UWJ_PingPongMgr::SetState(EPingPongState state)
{
	m_state = state;
}

EPingPongState UWJ_PingPongMgr::GetState()
{
	return m_state;
}

void UWJ_PingPongMgr::StartRally()
{
	SetState(EPingPongState::Rally);
	// ���� ī��Ʈ ����
	servCount++;
}

void UWJ_PingPongMgr::OnCollisionGround(int player, bool in)
{
	// ���� ��ȭ
	// ���� ������ �̵�

	if (in)
	{
		// player point ++
		if (player == 0)
		{
			pointA++;

			// if Deuce point ++
			if (bIsDeuce)
			{
				pointA++;
			}
		}
		else
		{
			pointB++;
			if (bIsDeuce)
			{
				pointB++;
			}
		}
		pointPannel->SetPoint(0, pointA);
		pointPannel->SetPoint(1, pointB);
	}
	else
	{
		// other player point ++
		// if Deuce point ++
		if (player == 0)
		{
			pointB++;

			if (bIsDeuce)
			{
				pointB++;
			}
		}
		else
		{
			pointA++;
			if (bIsDeuce)
			{
				pointA++;
			}
		}
		pointPannel->SetPoint(0, pointA);
		pointPannel->SetPoint(1, pointB);
	}

	//serv ����
	if (servCount >= 2)
	{
		bServPlayer = !bServPlayer;
		servCount = 0;
	}

	// �ེ 2���� �̻� ��Ʈ ����
	if (bIsDeuce)
	{
		if (pointA - pointB >= 2 || pointA - pointB <= -2)
		{
			// ���ھ� ���
			if (pointA > pointB)
			{
				scoreA++;
			}
			else
			{
				scoreB++;
			}

			scorePannel->SetPoint(0,scoreA);
			scorePannel->SetPoint(1,scoreB);

			SetState(EPingPongState::SetOver);
			return;
		}
	}
	else 
	{
		// �ེ �ƴ� ��� 11�� ȹ��� ��Ʈ ����
		if (pointA == 11 || pointB == 11)
		{
			// ���ھ� ���
			if (pointA == 11)
			{
				scoreA++;
			}
			else
			{
				scoreB++;
			}

			scorePannel->SetPoint(0, scoreA);
			scorePannel->SetPoint(1, scoreB);

			SetState(EPingPongState::SetOver);
			return;
		}
	}

	if (pointA == 10 && pointB == 10)
	{
		bIsDeuce = true;
	}

	SetState(EPingPongState::Serv);
}

void UWJ_PingPongMgr::NetServ()
{
	// ���� �� ����
	
	SetState(EPingPongState::Serv);
}