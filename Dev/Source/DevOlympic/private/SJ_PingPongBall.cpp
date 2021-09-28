// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PingPongBall.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SJ_PingPongPlayer.h"
#include "SJ_PingPongTableSideA.h"
#include "SJ_PingPongTableSideB.h"
#include "SJ_Net.h"
#include "VRGameModeBase.h"
#include "WJ_PingPongMgr.h"
#include "WJ_PPSingleModeWall.h"

// Sets default values
ASJ_PingPongBall::ASJ_PingPongBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	wrapFX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WrapFX"));
	wrapFX->SetupAttachment(meshComp);
	wrapFX->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASJ_PingPongBall::BeginPlay()
{
	Super::BeginPlay();

	meshComp->OnComponentHit.AddDynamic(this, &ASJ_PingPongBall::OnHit);
}

// Called every frame
void ASJ_PingPongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_PingPongBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	//UE_LOG(LogTemp, Warning, TEXT("playerID %d, ASide %d, BSide %d"), playerID, inSideA, inSideB);
	
	// ó�� ���� �ɶ��� �߷��� ���� �Ǿ� ���� �ʰ� ���� ȿ���� ��Ÿ����.
	// ���� �������� ���� ĥ���� �߷��� ���� ���ְ� ȿ���� ���ش�.
	meshComp->SetEnableGravity(true);
	wrapFX->SetVisibility(false);

	auto sideA = Cast<ASJ_PingPongTableSideA>(OtherActor);
	auto sideB = Cast<ASJ_PingPongTableSideB>(OtherActor);
	auto net = Cast<ASJ_Net>(OtherActor);
	auto player = Cast<ASJ_PingPongPlayer>(OtherActor);
	auto singleWall = Cast<AWJ_PPSingleModeWall>(OtherActor);

	// ���� ��� ��������
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	// Ź�� ���Ӹ�� ����
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// �̸��˻�
	FString name = OtherActor->GetName();

	/*
	// ���� �÷ο� ���¸ӽ� ���� -> ����
	if (pingpongMNG->GetState() == EPingPongState::Serv)
	{
		pingpongMNG->StartRally();

		// ���� ��� �� ���긦 �ϱ� ������ ���⼭ �Լ� ȣ�� ���� �ʱ�ȭ
		isCallScoreGet = false;
	}
	//*/

	// �÷��̾� SideA �� �ε����� ��
	if (sideA)
	{
		// SideA �� ó�� �浹 ���� ��
		if (inSideA == false)
		{
			inSideA = true;
		}
		// ���ϻ��̵� �ߺ� �浹 �� ����(true �� �� �� �浹)
		else if (inSideA == true)
		{
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}

		// ����
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// �÷��̾�B ���� ����! PlayerB�� �ڽ��� ���̵带 ������ �ʰ� PlayerA �� ���̵带 ������ ��
			if (playerID == 1 && inSideB == false)
			{
				// �÷��̾� B ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ���ú�
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// �� ���� �� ��, �� ���̵忡 ������. (�÷��̾�A ID = 0)
			if (playerID == 0)
			{
				// �÷��̾�A ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}

		// ���� ���
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// �÷��̾� SideB �� �ε����� ��
	else if (sideB)
	{
		// SideA�� �����ϰ�
		if (inSideB == false)
		{
			inSideB = true;
		}
		else if (inSideB == true)
		{
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}

		// ����
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// �÷��̾�A ���� ����! �÷��̾�A�� �ڽ��� ���̵带 ������ �ʰ� PlayerB�� ���̵带 ������ ��
			if (playerID == 0 && inSideA == false)
			{
				// �÷��̾�A ���� ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ���ú�
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// �� ���� �� ��, �� ���̵忡 ������. (�÷��̾�B ID = 1)
			if (playerID == 1)
			{
				// �÷��̾�B ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ���� ���
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// ��Ʈ�� �ε�������
	else if (net)
	{
		// ����
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ���� ���� �����̰� � ���̵忡�� �ε����� �ʾҴٸ�
			if (inSideA == false && inSideB == false)
			{
				// �ٽ� ����
				pingpongMNG->NetServ();
			}
			// �÷��̾�A�� �ڽ��� ���̵带 ���߰� ��Ʈ�� ��������
			else if (inSideA == true && inSideB == false)
			{
				// �÷��̾�A�� ���� (���� �̽�)
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
			// �÷��̾�B�� �ڽ��� ���̵带 ���߰� ��Ʈ�� �­�����
			else if (inSideA == false && inSideB == true)
			{
				// PlayerB�� ���� (���� �̽�)
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		else if (vrGameMNG->pingpongStateMgr->p_State == EPPBallState::Recive)
		{
			// ���ú� ���¿��� ��Ʈ�� ������ ���������� ���� ģ �÷��̾ ����
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}
	}
	// �÷��̾ ���� ��
	else if (player)
	{
		// �÷��̾� A �� ���� ��
		playerID = 0;

		if (pingpongMNG->GetState() == EPingPongState::Serv)
		{
			pingpongMNG->StartRally();

			// ���� ��� �� ���긦 �ϱ� ������ ���⼭ �Լ� ȣ�� ���� �ʱ�ȭ
			isCallScoreGet = false;
		}

		// ����
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ���갡 ������ �Ѿ���� ������ �̾���
			if (inSideA == true && inSideB == true)
			{
				pingpongMNG->p_State = EPPBallState::Recive;
			}
		}
		// ���ú�
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ���� �� ���� �ְ� �ޱⰡ ���� �ϸ� SideA,B �浹 ���θ� �ʱ�ȭ �Ѵ�.
			if (inSideA == true && inSideB == true)
			{
				InitSideState();
			}
		}

		// ���� ���
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	else if (singleWall) // �÷��̾� B ���� �߰�
	{
		// �÷��̾� B �� ���� ��
		playerID = 1;

		// ����
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ���갡 ������ �Ѿ���� ������ �̾���
			if (inSideA == true && inSideB == true)
			{
				pingpongMNG->p_State = EPPBallState::Recive;
			}
		}
		// ���ú�
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ���� �� ���� �ְ� �ޱⰡ ���� �ϸ� SideA,B �浹 ���θ� �ʱ�ȭ �Ѵ�.
			if (inSideA == true && inSideB == true)
			{
				InitSideState();
			}
		}

		// ���� ���
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// ��ܷ� �Ǽ� �ٴڿ� �ε�������
	else if (name.Contains("Floor"))
	{
		// ���� 
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{

			// A, B �� �� �浹 �� �׶���� ����
			if (inSideA == true && inSideB == true)
			{
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, true);
				}
			}
			// ���긦 �ߴµ� ��ܷ� ���� �� -> ���� �� �÷��̾ ���� 
			else
			{
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ���ú�
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// �÷��̾� B �� ���ú긦 ���� �� �� �÷��̾� A �� �޾� ġ�� ������ ��
			if (playerID == 1 && inSideA == true)
			{
				// �÷��̾�B ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, true);
				}
			}
			// �÷��̾� A �� ���ú긦 ���� �� �� �÷��̾� B �� �޾� ġ�� ������ ��
			else if (playerID == 0 && inSideB == true)
			{
				// �÷��̾� A ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, true);
				}
			}
			// �÷��̾� A �� ���ú긦 �ϰ� ��ܷ� ������ ��
			else if (playerID == 0)
			{
				// �÷��̾� A ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
			// �÷��̾� B �� ���ú긦 �ϰ� ��ܷ� ������ ��
			else if (playerID == 1)
			{
				// �÷��̾� B ����
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
	}
}

void ASJ_PingPongBall::InitSideState()
{
	inSideA = false;
	inSideB = false;
}

void ASJ_PingPongBall::ScoreGet(int id, bool scoreCheck)
{
	// ���� ��� ��������
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	// Ź�� ���Ӹ�� ����
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// ���� ��� �Լ�
	pingpongMNG->OnCollisionGround(id, scoreCheck);
	// �浹 �ʱ�ȭ
	inSideA = false;
	inSideB = false;
	// �÷��̾� ID �ʱ�ȭ
	playerID = -1;
	// �� ���� Ÿ�̸�
	GetWorldTimerManager().SetTimer(destroyHandle, this, &ASJ_PingPongBall::BallDestroy, 3.0f);
	// �Լ� ȣ�� ����
	isCallScoreGet = true;
}

void ASJ_PingPongBall::BallDestroy()
{
	Destroy();
}

