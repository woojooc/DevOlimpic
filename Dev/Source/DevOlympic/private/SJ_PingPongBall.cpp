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
	
	// Ã³À½ »ý¼º µÉ¶§´Â Áß·ÂÀÌ Àû¿ë µÇ¾î ÀÖÁö ¾Ê°í »ý¼º È¿°úµµ ³ªÅ¸³­´Ù.
	// µû¶ó¼­ ¶óÄÏÀ¸·Î °øÀ» Ä¥¶§´Â Áß·ÂÀ» Àû¿ë ÇØÁÖ°í È¿°úµµ ²¨ÁØ´Ù.
	meshComp->SetEnableGravity(true);
	wrapFX->SetVisibility(false);

	auto sideA = Cast<ASJ_PingPongTableSideA>(OtherActor);
	auto sideB = Cast<ASJ_PingPongTableSideB>(OtherActor);
	auto net = Cast<ASJ_Net>(OtherActor);
	auto player = Cast<ASJ_PingPongPlayer>(OtherActor);
	auto singleWall = Cast<AWJ_PPSingleModeWall>(OtherActor);

	// °ÔÀÓ ¸ðµå °¡Á®¿À±â
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	// Å¹±¸ °ÔÀÓ¸ðµå º¯¼ö
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// ÀÌ¸§°Ë»ç
	FString name = OtherActor->GetName();

	/*
	// °ÔÀÓ ÇÃ·Î¿ì »óÅÂ¸Ó½Å ¼­ºê -> ·¤¸®
	if (pingpongMNG->GetState() == EPingPongState::Serv)
	{
		pingpongMNG->StartRally();

		// Á¡¼ö °è»ê ÈÄ ¼­ºê¸¦ ÇÏ±â ¶§¹®¿¡ ¿©±â¼­ ÇÔ¼ö È£Ãâ ¿©ºÎ ÃÊ±âÈ­
		isCallScoreGet = false;
	}
	//*/

	// ÇÃ·¹ÀÌ¾î SideA ¿¡ ºÎµúÇûÀ» ¶§
	if (sideA)
	{
		// SideA ¿¡ Ã³À½ Ãæµ¹ ÇßÀ» ¶§
		if (inSideA == false)
		{
			inSideA = true;
		}
		// µ¿ÀÏ»çÀÌµå Áßº¹ Ãæµ¹ ½Ã ½ÇÁ¡(true ÀÏ ¶§ ¶Ç Ãæµ¹)
		else if (inSideA == true)
		{
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}

		// ¼­ºê
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ÇÃ·¹ÀÌ¾îB ¼­ºê ½ÇÆÐ! PlayerB°¡ ÀÚ½ÅÀÇ »çÀÌµå¸¦ ¸ÂÃßÁö ¾Ê°í PlayerA ÀÇ »çÀÌµå¸¦ ¸ÂÃèÀ» ¶§
			if (playerID == 1 && inSideB == false)
			{
				// ÇÃ·¹ÀÌ¾î B ½ÇÁ¡
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ¸®½Ãºê
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ³» ¼ø¼­ ÀÏ ¶§, ³» »çÀÌµå¿¡ ¸ÂÀ¸¸é. (ÇÃ·¹ÀÌ¾îA ID = 0)
			if (playerID == 0)
			{
				// ÇÃ·¹ÀÌ¾îA ½ÇÁ¡
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}

		// »ç¿îµå Àç»ý
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// ÇÃ·¹ÀÌ¾î SideB ¿¡ ºÎµúÇûÀ» ¶§
	else if (sideB)
	{
		// SideA¿Í µ¿ÀÏÇÏ°Ô
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

		// ¼­ºê
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ÇÃ·¹ÀÌ¾îA ¼­ºê ½ÇÆÐ! ÇÃ·¹ÀÌ¾îA°¡ ÀÚ½ÅÀÇ »çÀÌµå¸¦ ¸ÂÃßÁö ¾Ê°í PlayerBÀÇ »çÀÌµå¸¦ ¸ÂÃèÀ» ¶§
			if (playerID == 0 && inSideA == false)
			{
				// ÇÃ·¹ÀÌ¾îA ¼­ºê ½ÇÆÐ
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ¸®½Ãºê
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ³» ¼ø¼­ ÀÏ ¶§, ³» »çÀÌµå¿¡ ¸ÂÀ¸¸é. (ÇÃ·¹ÀÌ¾îB ID = 1)
			if (playerID == 1)
			{
				// ÇÃ·¹ÀÌ¾îB ½ÇÁ¡
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// »ç¿îµå Àç»ý
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// ³×Æ®¿¡ ºÎµúÇûÀ»¶§
	else if (net)
	{
		// ¼­ºê
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ¸¸¾à ¼­ºê »óÅÂÀÌ°í ¾î¶² »çÀÌµå¿¡µµ ºÎµúÈ÷Áö ¾Ê¾Ò´Ù¸é
			if (inSideA == false && inSideB == false)
			{
				// ´Ù½Ã ¼­ºê
				pingpongMNG->NetServ();
			}
			// ÇÃ·¹ÀÌ¾îA°¡ ÀÚ½ÅÀÇ »çÀÌµå¸¦ ¸ÂÃß°í ³×Æ®¸¦ ¸ÂÃèÀ»¶§
			else if (inSideA == true && inSideB == false)
			{
				// ÇÃ·¹ÀÌ¾îAÀÇ ½ÇÁ¡ (¼­ºê ¹Ì½º)
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
			// ÇÃ·¹ÀÌ¾îB°¡ ÀÚ½ÅÀÇ »çÀÌµå¸¦ ¸ÂÃß°í ³×Æ®¸¦ ¸Â­ŸÀ»¶§
			else if (inSideA == false && inSideB == true)
			{
				// PlayerBÀÇ ½ÇÁ¡ (¼­ºê ¹Ì½º)
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		else if (vrGameMNG->pingpongStateMgr->p_State == EPPBallState::Recive)
		{
			// ¸®½Ãºê »óÅÂ¿¡¼­ ³×Æ®¿¡ ¸ÂÀ¸¸é ¸¶Áö¸·À¸·Î °øÀ» Ä£ ÇÃ·¹ÀÌ¾î°¡ ½ÇÁ¡
			if (isCallScoreGet == false)
			{
				ScoreGet(playerID, false);
			}
		}
	}
	// ÇÃ·¹ÀÌ¾î°¡ ÃÆÀ» ¶§
	else if (player)
	{
		// ÇÃ·¹ÀÌ¾î A °¡ ÃÆÀ» ¶§
		playerID = 0;

		if (pingpongMNG->GetState() == EPingPongState::Serv)
		{
			pingpongMNG->StartRally();

			// Á¡¼ö °è»ê ÈÄ ¼­ºê¸¦ ÇÏ±â ¶§¹®¿¡ ¿©±â¼­ ÇÔ¼ö È£Ãâ ¿©ºÎ ÃÊ±âÈ­
			isCallScoreGet = false;
		}

		// ¼­ºê
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ¼­ºê°¡ ¹«»çÈ÷ ³Ñ¾î¿À¸é ·¤¸®·Î ÀÌ¾îÁü
			if (inSideA == true && inSideB == true)
			{
				pingpongMNG->p_State = EPPBallState::Recive;
			}
		}
		// ¸®½Ãºê
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ¼­·Î ÇÑ ¹ø¾¿ ÁÖ°í ¹Þ±â°¡ ¼º°ø ÇÏ¸é SideA,B Ãæµ¹ ¿©ºÎ¸¦ ÃÊ±âÈ­ ÇÑ´Ù.
			if (inSideA == true && inSideB == true)
			{
				InitSideState();
			}
		}

		// »ç¿îµå Àç»ý
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	else if (singleWall) // ÇÃ·¹ÀÌ¾î B ÃßÈÄ Ãß°¡
	{
		// ÇÃ·¹ÀÌ¾î B °¡ ÃÆÀ» ¶§
		playerID = 1;

		// ¼­ºê
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{
			// ¼­ºê°¡ ¹«»çÈ÷ ³Ñ¾î¿À¸é ·¤¸®·Î ÀÌ¾îÁü
			if (inSideA == true && inSideB == true)
			{
				pingpongMNG->p_State = EPPBallState::Recive;
			}
		}
		// ¸®½Ãºê
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ¼­·Î ÇÑ ¹ø¾¿ ÁÖ°í ¹Þ±â°¡ ¼º°ø ÇÏ¸é SideA,B Ãæµ¹ ¿©ºÎ¸¦ ÃÊ±âÈ­ ÇÑ´Ù.
			if (inSideA == true && inSideB == true)
			{
				InitSideState();
			}
		}

		// »ç¿îµå Àç»ý
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pingpongSound, GetActorLocation());
	}
	// Àå¿Ü·Î µÇ¼­ ¹Ù´Ú¿¡ ºÎµúÇûÀ»¶§
	else if (name.Contains("Floor"))
	{
		// ¼­ºê 
		if (pingpongMNG->p_State == EPPBallState::Serve)
		{

			// A, B µÑ ´Ù Ãæµ¹ ÈÄ ±×¶ó¿îµå½Ã µæÁ¡
			if (inSideA == true && inSideB == true)
			{
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, true);
				}
			}
			// ¼­ºê¸¦ Çß´Âµ¥ Àå¿Ü·Î ³ª°¥ ½Ã -> ¼­ºê ÇÑ ÇÃ·¹ÀÌ¾î°¡ ½ÇÁ¡ 
			else
			{
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
		}
		// ¸®½Ãºê
		else if (pingpongMNG->p_State == EPPBallState::Recive)
		{
			// ÇÃ·¹ÀÌ¾î B °¡ ¸®½Ãºê¸¦ ¼º°ø ÇÑ ÈÄ ÇÃ·¹ÀÌ¾î A °¡ ¹Þ¾Æ Ä¡Áö ¸øÇßÀ» ¶§
			if (playerID == 1 && inSideA == true)
			{
				// ÇÃ·¹ÀÌ¾îB µæÁ¡
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, true);
				}
			}
			// ÇÃ·¹ÀÌ¾î A °¡ ¸®½Ãºê¸¦ ¼º°ø ÇÑ ÈÄ ÇÃ·¹ÀÌ¾î B °¡ ¹Þ¾Æ Ä¡Áö ¸øÇßÀ» ¶§
			else if (playerID == 0 && inSideB == true)
			{
				// ÇÃ·¹ÀÌ¾î A µæÁ¡
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, true);
				}
			}
			// ÇÃ·¹ÀÌ¾î A °¡ ¸®½Ãºê¸¦ ÇÏ°í Àå¿Ü·Î ³ª°¬À» ¶§
			else if (playerID == 0)
			{
				// ÇÃ·¹ÀÌ¾î A ½ÇÁ¡
				if (isCallScoreGet == false)
				{
					ScoreGet(playerID, false);
				}
			}
			// ÇÃ·¹ÀÌ¾î B °¡ ¸®½Ãºê¸¦ ÇÏ°í Àå¿Ü·Î ³ª°¬À» ¶§
			else if (playerID == 1)
			{
				// ÇÃ·¹ÀÌ¾î B ½ÇÁ¡
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
	// °ÔÀÓ ¸ðµå °¡Á®¿À±â
	auto vrGameMNG = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	// Å¹±¸ °ÔÀÓ¸ðµå º¯¼ö
	UWJ_PingPongMgr* pingpongMNG = vrGameMNG->pingpongStateMgr;

	// Á¡¼ö °è»ê ÇÔ¼ö
	pingpongMNG->OnCollisionGround(id, scoreCheck);
	// Ãæµ¹ ÃÊ±âÈ­
	inSideA = false;
	inSideB = false;
	// ÇÃ·¹ÀÌ¾î ID ÃÊ±âÈ­
	playerID = -1;
	// °ø Á¦°Å Å¸ÀÌ¸Ó
	GetWorldTimerManager().SetTimer(destroyHandle, this, &ASJ_PingPongBall::BallDestroy, 3.0f);
	// ÇÔ¼ö È£Ãâ ¿©ºÎ
	isCallScoreGet = true;
}

void ASJ_PingPongBall::BallDestroy()
{
	Destroy();
}

