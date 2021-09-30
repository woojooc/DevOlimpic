#include "WJ_PingPongMgr.h"
#include "VRGameModeBase.h"
#include "WJ_ObjectPool.h"
#include "Kismet/GameplayStatics.h"
#include "ModeSelect.h"
#include "WJ_PPSingleModeWall.h"
#include "WJ_Point.h"
#include "SJ_PingPongPlayer.h"
#include "SJ_PingPongBall.h"


UWJ_PingPongMgr::UWJ_PingPongMgr()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWJ_PingPongMgr::BeginPlay()
{
	Super::BeginPlay();

	//gameModeBase ĳ��
	gameModeBase = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	
	// �� ĳ��
	AActor* wall = UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_PPSingleModeWall::StaticClass());

	// # ������ ĳ��
	TArray<AActor*> bpPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_Point::StaticClass(),bpPoints);

	if (gameModeBase->editMode == EEditMode::Multi)
	{
		// �� ��Ȱ��ȭ
		if (wall)
		{
			wall->SetActorHiddenInGame(true);
		}
		// �÷��̾� ȣ��Ʈ ( 0, A ) -> Ź���� ���̵� A
		// �÷��̾� �Խ�Ʈ ( 1, B ) -> Ź���� ���̵� B �� ��ȯ

		// ù ���� �������� �̱�
	}
	else
	{
		// # �÷��̾� ����
		playerActorA = UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_PingPongPlayer::StaticClass());
		
		// # �� Ȱ��ȭ
		if (wall)
		{
			playerActorB = wall;
			wall->SetActorHiddenInGame(false);
		}
		
		if (bpPoints.Num() != 0)
		{
			for (int i = 0; i < bpPoints.Num(); i++)
			{
				AWJ_Point* emptyPlace = nullptr;
				pointPannelarr.Add(emptyPlace);
			}

			for (int i = 0; i < bpPoints.Num(); i++)
			{
				auto pannel = Cast<AWJ_Point>(bpPoints[i]);
				pointPannelarr[pannel->order] = pannel;
			}

			pointPannelarr[0]->SetColor(FColor::Blue);
			pointPannelarr[1]->SetColor(FColor::Red);
			
			// �÷��̾� B ������ ��Ȱ��ȭ
			pointPannelarr[2]->SetActorHiddenInGame(true);
			pointPannelarr[3]->SetActorHiddenInGame(true);
		}

		// # ���� ����
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
	//SetState(EPingPongState::Serv);
}

void UWJ_PingPongMgr::Serv()
{
	// ���� �����Ǿ����� ���
	if (bSpawnBall)
	{
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("SERV player %d"), bServPlayer);

	// ������ �� �� �� ���� ��� ���� ���� �÷ο츦 ����� �ǵ�����.
	p_State = EPPBallState::Serve;

	// bServPlayer�� T -> A ��ġ�� �� ����
	// else -> B ��ġ�� �� ����
	if (bServPlayer == 0)
	{
		//A �� ����
		if (playerActorA)
		{
			ppball = gameModeBase->objectPool->GetPingPongBall(playerActorA,0, gameModeBase->editMode);
			bSpawnBall = true;
		}
	}
	else
	{
		//B �� ����
		ppball = gameModeBase->objectPool->GetPingPongBall(playerActorB,1, gameModeBase->editMode);
		bSpawnBall = true;

		// ���� ����
		if (gameModeBase->editMode == EEditMode::Single)
		{
			// ���� �� Ȱ��ȭ �� ���� �޾ƿ´�.  => �� ĳ��. �����ϱ�

			// �÷��̾� ���� ����Ʈ �� �� �߰��ϱ�
			// -> �� ~ �� ���̷� �� ���� ���� �ϰ� ���ϱ�, ���� �����ϰ� ���ϱ�
			if (ppball)
			{
				FTimerHandle timer;
				GetWorld()->GetTimerManager().SetTimer(timer, this, &UWJ_PingPongMgr::autoServe, 3, false);

				/*
				// Ÿ�� ���� ����
				float x = FMath::RandRange(-30, -128);
				float y = FMath::RandRange(-75, 75);
				float z = FMath::RandRange(92, 160);
				FVector dir = FVector{ x, y, z } - ppball->GetActorLocation();
				dir.Normalize();

				sServePower = FMath::RandRange(1200,2200);

				// ���� �� �߰��ϱ�
				ppball->meshComp->SetEnableGravity(true);
				ppball->meshComp->AddForce(dir * sServePower);
				StartRally();
				//*/

				// TEST CODE
				/*
				FTimerHandle timer;
				GetWorld()->GetTimerManager().SetTimer(timer,this, &UWJ_PingPongMgr::autoServe, 2,false);
				//autoServe();
				//*/
				// END TEXT CODE
			}
		}
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
	if (scoreA == 2 || scoreB == 2 || set == scoreM)
	{
		SetState(EPingPongState::MatchOver);
		return;
	}
	pointA = 0;
	pointB = 0;
	
	pointPannelarr[0]->ResetPoint();

	set++;
	SetState(EPingPongState::Serv);
}

void UWJ_PingPongMgr::MatchOver()
{
	if (scoreA > scoreB)
	{
		// A �¸�
		gameModeBase->SetWinner(0);
	}
	else
	{
		// B �¸�
		gameModeBase->SetWinner(1);
	}

	// ���� ���� �κ�� ���ư��� ��ư ������Ʈ Ȱ��ȭ
	gameModeBase->SetLevelState(EPPLevelState::GameOver);
}



void UWJ_PingPongMgr::StartRally()
{
	SetState(EPingPongState::Rally);
	// ���� ī��Ʈ ����
	servCount++;
	bSpawnBall = false;
}

void UWJ_PingPongMgr::OnCollisionGround(int player, bool in)
{
	// ���� ��ȭ
	// ���� ������ �̵�
	//UE_LOG(LogTemp, Warning, TEXT("OnCollisionGround"));

	if (in)
	{
		// ����
		// player point ++
		if (player == 0)
		{
			pointA++;
		}
		else if(player == 1)
		{
			pointB++;
		}
		else
		{
			// TODO DEBUG
			//UE_LOG(LogTemp, Warning, TEXT("player -1, in true"));
		}

		pointPannelarr[0]->SetPoint(0, pointA);
		pointPannelarr[0]->SetPoint(1, pointB);
	}
	else
	{
		// ����
		// other player point ++
		if (player == 0)
		{
			pointB++;
		}
		else if (player == 1)
		{
			pointA++;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("player -1, in false"));
		}

		pointPannelarr[0]->SetPoint(0, pointA);
		pointPannelarr[0]->SetPoint(1, pointB);
	}

	//serv ����
	if (servCount >= 2)
	{
		//TODO �ּ� ����
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

			pointPannelarr[1]->SetPoint(0, scoreA);
			pointPannelarr[1]->SetPoint(1, scoreB);

			SetState(EPingPongState::SetOver);
			return;
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("5point"));

		// �ེ �ƴ� ��� 11�� ȹ��� ��Ʈ ����
		if (pointA == pointM || pointB == pointM)
		{
			// ���ھ� ���
			if (pointA == pointM)
			{
				scoreA++;
			}
			else
			{
				scoreB++;
			}

			pointPannelarr[1]->SetPoint(0, scoreA);
			pointPannelarr[1]->SetPoint(1, scoreB);

			SetState(EPingPongState::SetOver);
			return;
		}
	}

	// # ���� ���� �÷��̿��� �ེ ��� ����!!!
	/*
	if (pointA == pointM-1 && pointB == pointM-1)
	{
		bIsDeuce = true;
	}
	//*/

	SetState(EPingPongState::Serv);
}

void UWJ_PingPongMgr::NetServ()
{
	//UE_LOG(LogTemp, Warning, TEXT("NET SERVE AGAIN"));

	SetState(EPingPongState::Serv);
}


// # SINGLE MODE
void UWJ_PingPongMgr::autoServe()
{
	// Ÿ�� ���� ����
	float x = FMath::RandRange(-50, -128);
	float y = FMath::RandRange(-55, 55);
	float z = FMath::RandRange(95, 140);
	FVector dir = FVector{ x, y, z } - ppball->GetActorLocation();
	dir.Normalize();

	sServePower = FMath::RandRange(1350, 1500);

	// ���� �� �߰��ϱ�
	ppball->meshComp->SetEnableGravity(true);
	ppball->meshComp->AddForce(dir * sServePower);
	
	StartRally();

	// �ʱ�ȭ
	ppball->isCallScoreGet = false;
	ppball->playerID = 1;

	// TEST CODE
	/*
	ppball->SetActorLocation(FVector(120.f, 73, 126.5f));
	//ppball->SetActorLocation(FVector(120.f, 0, 126.5f));
	FVector dir = FVector(-120, -73, 100) - ppball->GetActorLocation();
	//FVector dir = FVector(-30, 0, 100) - ppball->GetActorLocation();
	dir.Normalize();

	ppball->meshComp->SetEnableGravity(true);
	ppball->meshComp->AddForce(dir * sServePower);
	//ppball = nullptr;
	StartRally();
	//*/
	// END TEST CODE
}


// # GET/ SET

void UWJ_PingPongMgr::SetState(EPingPongState state)
{
	m_state = state;
}

EPingPongState UWJ_PingPongMgr::GetState()
{
	return m_state;
}

void UWJ_PingPongMgr::SetFPPData(FPingPongData data)
{
	pointA = data.pointA;
	pointB = data.pointB;
	set = data.set;
	scoreA = data.scoreA;
	scoreB = data.scoreB;
	bServPlayer = data.bServPlayer;
	servCount = data.servCount;
	bSpawnBall = data.bSpawnBall;
	bIsDeuce = data.bIsDeuce;
}

FPingPongData UWJ_PingPongMgr::GetFPPData()
{
	fPPData.pointA = pointA;
	fPPData.pointB = pointB;
	fPPData.set = set;
	fPPData.scoreA = scoreA;
	fPPData.scoreB = scoreB;
	fPPData.bServPlayer = bServPlayer;
	fPPData.servCount = servCount;
	fPPData.bSpawnBall = bSpawnBall;
	fPPData.bIsDeuce = bIsDeuce;

	return fPPData;
}