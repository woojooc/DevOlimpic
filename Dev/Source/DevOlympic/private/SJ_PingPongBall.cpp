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
#include "SJ_OutOfZone.h"
#include "SH_PingPongBallRepComponent.h"

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

	ballRepComp = CreateDefaultSubobject<USH_PingPongBallRepComponent>(TEXT("RepComponent"));
}

// Called when the game starts or when spawned
void ASJ_PingPongBall::BeginPlay()
{
	Super::BeginPlay();

	canPingPongBallHit = true;
	meshComp->OnComponentHit.AddDynamic(this, &ASJ_PingPongBall::OnHit);
}

// Called every frame
void ASJ_PingPongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_PingPongBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// ���� ���� ����� ������ Hit �̺�Ʈ ������ ������ �ʰ� �ϱ� ����
	if (canPingPongBallHit == true)
	{

		// ó�� ���� �ɶ��� �߷��� ���� �Ǿ� ���� �ʰ� ���� ȿ���� ��Ÿ����.
		// ���� �������� ���� ĥ���� �߷��� ���� ���ְ� ȿ���� ���ش�.
		meshComp->SetEnableGravity(true);
		wrapFX->SetVisibility(false);

		auto sideA = Cast<ASJ_PingPongTableSideA>(OtherActor);
		auto sideB = Cast<ASJ_PingPongTableSideB>(OtherActor);
		auto net = Cast<ASJ_Net>(OtherActor);
		auto player = Cast<ASJ_PingPongPlayer>(OtherActor);
		auto singleWall = Cast<AWJ_PPSingleModeWall>(OtherActor);

		auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState());
		// Ź�� ���Ӹ�� ����
		UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

		// �̸��˻�
		FString name = OtherActor->GetName();

		// �÷��̾� SideA �� �ε����� ��
		if (sideA)
		{
			// �ߺ� �浹 �˻�
			overlapB = 0;
			overlapA++;

			// SideA �浹 ����
			if (inSideA == false)
			{
				inSideA = true;
			}

			// �÷��̾�A�� ���� �õ��� �� ���̵忡 �°� �ѱ��� ���ϰ� �����̵忡 �ٽ� ������ ����
			if (pingpongMNG->p_State == EPPBallState::Serve && overlapA >= 2 && playerID == 0)
			{
				// ���ϻ��̵� �ߺ� �浹 �� ����(true �� �� �� �浹)		
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Serve Overlap A"));
					ScoreGet(playerID, false);
				}
			}
			// �÷��̾� B�� ���긦 �����ߴµ� �÷��̾� A�� ������ ��
			else if (pingpongMNG->p_State == EPPBallState::Serve && overlapA >= 2 && playerID == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerB Serve Attack Success"));
				ScoreGet(playerID, true);
			}
			// �÷��̾�B�� ���ú긦 ���� �ϰ� �÷��̾�A�� ���ú긦 �����Ͽ� ���� ���̵忡 �ι� ������
			else if (pingpongMNG->p_State == EPPBallState::Recive && overlapA >= 2 && overlapB == 0)
			{
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Recive Overlap A"));
					ScoreGet(playerID, true);
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
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Serve Fail"));
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
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Recieve SideA"));
						ScoreGet(playerID, false);
					}
				}
			}

			// ȿ�� ���
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitPointFX, GetActorLocation());

			// ���� ���
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		// �÷��̾� SideB �� �ε����� ��
		else if (sideB)
		{
			// �ߺ� �浹 �˻�
			overlapA = 0;
			overlapB++;

			if (inSideB == false)
			{
				inSideB = true;
			}

			// �÷��̾�B�� ���� �õ� �� �� ���̵忡 �°� �ѱ��� ���ϰ� �� ���̵忡 �ٽ� ������ ����
			if (pingpongMNG->p_State == EPPBallState::Serve && overlapB >= 2 && playerID == 1)
			{
				// ���ϻ��̵� �ߺ� �浹 �� ����(true �� �� �� �浹)		
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Serve Overlap B"));
					ScoreGet(playerID, false);
				}
			}
			// �÷��̾� A�� ���긦 �����ߴµ� �÷��̾� B�� ������ ��
			else if (pingpongMNG->p_State == EPPBallState::Serve && overlapB >= 2 && playerID == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerB Serve Attack Success"));
				ScoreGet(playerID, true);
			}
			// �÷��̾�A�� ���ú긦 ���� �ϰ� �÷��̾�B�� ���ú긦 �����Ͽ� ���� ���̵忡 �ι� ������
			else if (pingpongMNG->p_State == EPPBallState::Recive && overlapB >= 2 && overlapA == 0)
			{
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Receive Overlap A"));
					ScoreGet(playerID, true);
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
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Serve Fail"));
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
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Recieve SideB"));
						ScoreGet(playerID, false);
					}
				}
			}
			// ȿ�� ���
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitPointFX, GetActorLocation());
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
					UE_LOG(LogTemp, Warning, TEXT("NetServe"));
					// �ٽ� ����
					EndOfBall();
				}
			}
		}
		// �÷��̾ ���� ��
		else if (player && player->playerIndex == 0)
		{
			// ��ƽ ȿ��
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitFxHaptic, EControllerHand::Right, 0.3f, false);

			// �÷��̾� A �� ���� ��
			playerID = 0;

			// ����
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("StartRally"));
					pingpongMNG->StartRally();

					// ���� ��� �� ���긦 �ϱ� ������ ���⼭ �Լ� ȣ�� ���� �ʱ�ȭ
					isCallScoreGet = false;
				}
				// ���갡 ������ �Ѿ���� ������ �̾���
				else if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Next Receive"));
					pingpongMNG->p_State = EPPBallState::Recive;
				}
			}
			// ���ú�
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// ���� �� ���� �ְ� �ޱⰡ ���� �ϸ� SideA,B �浹 ���θ� �ʱ�ȭ �Ѵ�.
				if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Hit Position"));
					InitSideState();
				}
			}

			// ���� ���
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		else if (player && player->playerIndex == 1)
		{
			// �÷��̾� B �� ���� ��
			playerID = 1;

			// ����
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("StartRally"));
					pingpongMNG->StartRally();
					// ���� ��� �� ���긦 �ϱ� ������ ���⼭ �Լ� ȣ�� ���� �ʱ�ȭ
					isCallScoreGet = false;
				}
				// ���갡 ������ �Ѿ���� ������ �̾���
				else if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Next Receive"));
					pingpongMNG->p_State = EPPBallState::Recive;
				}
			}
			// ���ú�
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// ���� �� ���� �ְ� �ޱⰡ ���� �ϸ� SideA,B �浹 ���θ� �ʱ�ȭ �Ѵ�.
				if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Hit Position"));
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
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("StartRally"));
					pingpongMNG->StartRally();
					// ���� ��� �� ���긦 �ϱ� ������ ���⼭ �Լ� ȣ�� ���� �ʱ�ȭ
					isCallScoreGet = false;
				}
				// ���갡 ������ �Ѿ���� ������ �̾���
				else if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Next Receive"));
					pingpongMNG->p_State = EPPBallState::Recive;
				}
			}
			// ���ú�
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// ���� �� ���� �ְ� �ޱⰡ ���� �ϸ� SideA,B �浹 ���θ� �ʱ�ȭ �Ѵ�.
				if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Hit Position"));
					InitSideState();
				}
			}

			// ���� ���
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		// ��ܷ� �Ǽ� �ٴڿ� �ε�������
		else if (name.Contains("Floor")) // �� �κ� ��� ���� ó�� ����
		{
			// ���� 
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{

				// A, B �� �� �浹 �� �׶���� ����
				if (inSideA == true && inSideB == true)
				{
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("Serve Point Up"));
						ScoreGet(playerID, true);
					}
				}
				// ���긦 �ߴµ� ��ܷ� ���� �� -> ���� �� �÷��̾ ���� 
				else
				{
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("Serve Point Down"));
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
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Attack Success"));
						ScoreGet(playerID, true);
					}
				}
				// �÷��̾� A �� ���ú긦 ���� �� �� �÷��̾� B �� �޾� ġ�� ������ ��
				else if (playerID == 0 && inSideB == true)
				{
					// �÷��̾� A ����
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Attack Success"));
						ScoreGet(playerID, true);
					}
				}
				// �÷��̾� A �� ���ú긦 �ϰ� ��ܷ� ������ ��
				else if (playerID == 0)
				{
					// �÷��̾� A ����
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Attack Fail"));
						ScoreGet(playerID, false);
					}
				}
				// �÷��̾� B �� ���ú긦 �ϰ� ��ܷ� ������ ��
				else if (playerID == 1)
				{
					// �÷��̾� B ����
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Attack Fail"));
						ScoreGet(playerID, false);
					}
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
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState());
	// Ź�� ���Ӹ�� ����
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// ���� ��� �Լ�
	pingpongMNG->OnCollisionGround(id, scoreCheck);

	// �浹 �ʱ�ȭ
	inSideA = false;
	inSideB = false;

	// �÷��̾� ID �ʱ�ȭ
	playerID = -1;

	// ���� ȹ�� ����
	UGameplayStatics::PlaySound2D(GetWorld(), scoreSound);

	// �� ���� Ÿ�̸�
	GetWorldTimerManager().SetTimer(destroyHandle, this, &ASJ_PingPongBall::EndOfBall, 3.0f);

	// �Լ� ȣ�� ����
	isCallScoreGet = true;

	// HIt�̺�Ʈ ���� ����
	canPingPongBallHit = false;
}

void ASJ_PingPongBall::EndOfBall()
{
	// ���� ��� ��������
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState());
	// Ź�� ���Ӹ�� ����
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	if (pingpongMNG->GetState() == EPingPongState::SetOver || pingpongMNG->GetState() == EPingPongState::MatchOver)
	{
		Destroy();
		return;
	}
	else
	{
		pingpongMNG->SetState(EPingPongState::Serv);
		Destroy();
	}
}

void ASJ_PingPongBall::ZoneExit()
{
	// ���� ��� ��������
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState()
		
		);
	// Ź�� ���Ӹ�� ����
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

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

