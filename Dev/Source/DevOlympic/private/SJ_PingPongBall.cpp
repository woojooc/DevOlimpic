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
	// 공이 점수 계산을 끝내면 Hit 이벤트 연산을 해주지 않게 하기 위함
	if (canPingPongBallHit == true)
	{

		// 처음 생성 될때는 중력이 적용 되어 있지 않고 생성 효과도 나타난다.
		// 따라서 라켓으로 공을 칠때는 중력을 적용 해주고 효과도 꺼준다.
		meshComp->SetEnableGravity(true);
		wrapFX->SetVisibility(false);

		auto sideA = Cast<ASJ_PingPongTableSideA>(OtherActor);
		auto sideB = Cast<ASJ_PingPongTableSideB>(OtherActor);
		auto net = Cast<ASJ_Net>(OtherActor);
		auto player = Cast<ASJ_PingPongPlayer>(OtherActor);
		auto singleWall = Cast<AWJ_PPSingleModeWall>(OtherActor);

		auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState());
		// 탁구 게임모드 변수
		UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

		// 이름검사
		FString name = OtherActor->GetName();

		// 플레이어 SideA 에 부딪혔을 때
		if (sideA)
		{
			// 중복 충돌 검사
			overlapB = 0;
			overlapA++;

			// SideA 충돌 여부
			if (inSideA == false)
			{
				inSideA = true;
			}

			// 플레이어A가 서브 시도시 내 사이드에 맞고 넘기지 못하고 내사이드에 다시 맞으면 실점
			if (pingpongMNG->p_State == EPPBallState::Serve && overlapA >= 2 && playerID == 0)
			{
				// 동일사이드 중복 충돌 시 실점(true 일 때 또 충돌)		
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Serve Overlap A"));
					ScoreGet(playerID, false);
				}
			}
			// 플레이어 B가 서브를 성공했는데 플레이어 A가 못받을 시
			else if (pingpongMNG->p_State == EPPBallState::Serve && overlapA >= 2 && playerID == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerB Serve Attack Success"));
				ScoreGet(playerID, true);
			}
			// 플레이어B가 리시브를 성공 하고 플레이어A가 리시브를 실패하여 같은 사이드에 두번 맞으면
			else if (pingpongMNG->p_State == EPPBallState::Recive && overlapA >= 2 && overlapB == 0)
			{
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Recive Overlap A"));
					ScoreGet(playerID, true);
				}
			}

			// 서브
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				// 플레이어B 서브 실패! PlayerB가 자신의 사이드를 맞추지 않고 PlayerA 의 사이드를 맞췄을 때
				if (playerID == 1 && inSideB == false)
				{
					// 플레이어 B 실점
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Serve Fail"));
						ScoreGet(playerID, false);
					}
				}
			}
			// 리시브
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// 내 순서 일 때, 내 사이드에 맞으면. (플레이어A ID = 0)
				if (playerID == 0)
				{
					// 플레이어A 실점
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Recieve SideA"));
						ScoreGet(playerID, false);
					}
				}
			}

			// 효과 재생
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitPointFX, GetActorLocation());

			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		// 플레이어 SideB 에 부딪혔을 때
		else if (sideB)
		{
			// 중복 충돌 검사
			overlapA = 0;
			overlapB++;

			if (inSideB == false)
			{
				inSideB = true;
			}

			// 플레이어B가 서브 시도 시 내 사이드에 맞고 넘기지 못하고 내 사이드에 다시 맞으면 실점
			if (pingpongMNG->p_State == EPPBallState::Serve && overlapB >= 2 && playerID == 1)
			{
				// 동일사이드 중복 충돌 시 실점(true 일 때 또 충돌)		
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Serve Overlap B"));
					ScoreGet(playerID, false);
				}
			}
			// 플레이어 A가 서브를 성공했는데 플레이어 B가 못받을 시
			else if (pingpongMNG->p_State == EPPBallState::Serve && overlapB >= 2 && playerID == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerB Serve Attack Success"));
				ScoreGet(playerID, true);
			}
			// 플레이어A가 리시브를 성공 하고 플레이어B가 리시브를 실패하여 같은 사이드에 두번 맞으면
			else if (pingpongMNG->p_State == EPPBallState::Recive && overlapB >= 2 && overlapA == 0)
			{
				if (isCallScoreGet == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Receive Overlap A"));
					ScoreGet(playerID, true);
				}
			}

			// 서브
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				// 플레이어A 서브 실패! 플레이어A가 자신의 사이드를 맞추지 않고 PlayerB의 사이드를 맞췄을 때
				if (playerID == 0 && inSideA == false)
				{
					// 플레이어A 서브 실패
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Serve Fail"));
						ScoreGet(playerID, false);
					}
				}
			}
			// 리시브
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// 내 순서 일 때, 내 사이드에 맞으면. (플레이어B ID = 1)
				if (playerID == 1)
				{
					// 플레이어B 실점
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Recieve SideB"));
						ScoreGet(playerID, false);
					}
				}
			}
			// 효과 재생
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitPointFX, GetActorLocation());
			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		// 네트에 부딪혔을때
		else if (net)
		{
			// 서브
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				// 만약 서브 상태이고 어떤 사이드에도 부딪히지 않았다면
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("NetServe"));
					// 다시 서브
					EndOfBall();
				}
			}
		}
		// 플레이어가 쳤을 때
		else if (player && player->playerIndex == 0)
		{
			// 햅틱 효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitFxHaptic, EControllerHand::Right, 0.3f, false);

			// 플레이어 A 가 쳤을 때
			playerID = 0;

			// 서브
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("StartRally"));
					pingpongMNG->StartRally();

					// 점수 계산 후 서브를 하기 때문에 여기서 함수 호출 여부 초기화
					isCallScoreGet = false;
				}
				// 서브가 무사히 넘어오면 랠리로 이어짐
				else if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Next Receive"));
					pingpongMNG->p_State = EPPBallState::Recive;
				}
			}
			// 리시브
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// 서로 한 번씩 주고 받기가 성공 하면 SideA,B 충돌 여부를 초기화 한다.
				if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Hit Position"));
					InitSideState();
				}
			}

			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		else if (player && player->playerIndex == 1)
		{
			// 플레이어 B 가 쳤을 때
			playerID = 1;

			// 서브
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("StartRally"));
					pingpongMNG->StartRally();
					// 점수 계산 후 서브를 하기 때문에 여기서 함수 호출 여부 초기화
					isCallScoreGet = false;
				}
				// 서브가 무사히 넘어오면 랠리로 이어짐
				else if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Next Receive"));
					pingpongMNG->p_State = EPPBallState::Recive;
				}
			}
			// 리시브
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// 서로 한 번씩 주고 받기가 성공 하면 SideA,B 충돌 여부를 초기화 한다.
				if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Hit Position"));
					InitSideState();
				}
			}

			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		else if (singleWall) // 플레이어 B 추후 추가
		{
			// 플레이어 B 가 쳤을 때
			playerID = 1;

			// 서브
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{
				if (inSideA == false && inSideB == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("StartRally"));
					pingpongMNG->StartRally();
					// 점수 계산 후 서브를 하기 때문에 여기서 함수 호출 여부 초기화
					isCallScoreGet = false;
				}
				// 서브가 무사히 넘어오면 랠리로 이어짐
				else if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Next Receive"));
					pingpongMNG->p_State = EPPBallState::Recive;
				}
			}
			// 리시브
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// 서로 한 번씩 주고 받기가 성공 하면 SideA,B 충돌 여부를 초기화 한다.
				if (inSideA == true && inSideB == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Hit Position"));
					InitSideState();
				}
			}

			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
		}
		// 장외로 되서 바닥에 부딪혔을때
		else if (name.Contains("Floor")) // 이 부분 장외 범위 처리 예정
		{
			// 서브 
			if (pingpongMNG->p_State == EPPBallState::Serve)
			{

				// A, B 둘 다 충돌 후 그라운드시 득점
				if (inSideA == true && inSideB == true)
				{
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("Serve Point Up"));
						ScoreGet(playerID, true);
					}
				}
				// 서브를 했는데 장외로 나갈 시 -> 서브 한 플레이어가 실점 
				else
				{
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("Serve Point Down"));
						ScoreGet(playerID, false);
					}
				}
			}
			// 리시브
			else if (pingpongMNG->p_State == EPPBallState::Recive)
			{
				// 플레이어 B 가 리시브를 성공 한 후 플레이어 A 가 받아 치지 못했을 때
				if (playerID == 1 && inSideA == true)
				{
					// 플레이어B 득점
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerB Attack Success"));
						ScoreGet(playerID, true);
					}
				}
				// 플레이어 A 가 리시브를 성공 한 후 플레이어 B 가 받아 치지 못했을 때
				else if (playerID == 0 && inSideB == true)
				{
					// 플레이어 A 득점
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Attack Success"));
						ScoreGet(playerID, true);
					}
				}
				// 플레이어 A 가 리시브를 하고 장외로 나갔을 때
				else if (playerID == 0)
				{
					// 플레이어 A 실점
					if (isCallScoreGet == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("PlayerA Attack Fail"));
						ScoreGet(playerID, false);
					}
				}
				// 플레이어 B 가 리시브를 하고 장외로 나갔을 때
				else if (playerID == 1)
				{
					// 플레이어 B 실점
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
	// 게임 모드 가져오기
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState());
	// 탁구 게임모드 변수
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// 점수 계산 함수
	pingpongMNG->OnCollisionGround(id, scoreCheck);

	// 충돌 초기화
	inSideA = false;
	inSideB = false;

	// 플레이어 ID 초기화
	playerID = -1;

	// 점수 획득 사운드
	UGameplayStatics::PlaySound2D(GetWorld(), scoreSound);

	// 공 제거 타이머
	GetWorldTimerManager().SetTimer(destroyHandle, this, &ASJ_PingPongBall::EndOfBall, 3.0f);

	// 함수 호출 여부
	isCallScoreGet = true;

	// HIt이벤트 연산 여부
	canPingPongBallHit = false;
}

void ASJ_PingPongBall::EndOfBall()
{
	// 게임 모드 가져오기
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState());
	// 탁구 게임모드 변수
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
	// 게임 모드 가져오기
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetGameState()
		
		);
	// 탁구 게임모드 변수
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// 서브 
	if (pingpongMNG->p_State == EPPBallState::Serve)
	{

		// A, B 둘 다 충돌 후 그라운드시 득점
		if (inSideA == true && inSideB == true)
		{
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, true);
			}
		}
		// 서브를 했는데 장외로 나갈 시 -> 서브 한 플레이어가 실점 
		else
		{
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}
	}
	// 리시브
	else if (pingpongMNG->p_State == EPPBallState::Recive)
	{
		// 플레이어 B 가 리시브를 성공 한 후 플레이어 A 가 받아 치지 못했을 때
		if (playerID == 1 && inSideA == true)
		{
			// 플레이어B 득점
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, true);
			}
		}
		// 플레이어 A 가 리시브를 성공 한 후 플레이어 B 가 받아 치지 못했을 때
		else if (playerID == 0 && inSideB == true)
		{
			// 플레이어 A 득점
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, true);
			}
		}
		// 플레이어 A 가 리시브를 하고 장외로 나갔을 때
		else if (playerID == 0)
		{
			// 플레이어 A 실점
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}
		// 플레이어 B 가 리시브를 하고 장외로 나갔을 때
		else if (playerID == 1)
		{
			// 플레이어 B 실점
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}
	}
}

