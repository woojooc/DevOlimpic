

#include "WJ_PingPongMgr.h"
#include "VRGameModeBase.h"
#include "WJ_ObjectPool.h"
#include "Kismet/GameplayStatics.h"
#include "ModeSelect.h"
#include "WJ_PPSingleModeWall.h"


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

	if (editMode == EEditMode::Multi)
	{
		// �÷��̾� ȣ��Ʈ ( 0, A ) -> Ź���� ���̵� A
		// �÷��̾� �Խ�Ʈ ( 1, B ) -> Ź���� ���̵� B �� ��ȯ

		// ù ���� �������� �̱�
	}
	else
	{
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
		Rally();
		break;

	case EPingPongState::RallyOver:
		// �� ����
		// ����(point) ȹ��
		// 10 : 10 ==> Serv, bIsDeuse = true : 2������������ �ݺ�
		// point < 11 ==> Serv
		// 11 ==> SetOver
		RallyOver();
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
		gameModeBase->objectPool->GetPingPongBall(0);
	}
	else
	{
		//B �� ����
		gameModeBase->objectPool->GetPingPongBall(1);
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
	if (set == 5)
	{
		SetState(EPingPongState::MatchOver);
		return;
	}

	set++;
	pointA = 0;
	pointB = 0;

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
		// if Deuce point ++
	}
	else
	{
		// other player point ++
		// if Deuce point ++
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