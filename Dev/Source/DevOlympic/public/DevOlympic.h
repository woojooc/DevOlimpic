// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Game Channel
#define ECC_Stadium			ECC_GameTraceChannel1
#define ECC_Avatar			ECC_GameTraceChannel2
#define ECC_LobbyPlayer		ECC_GameTraceChannel3
#define ECC_EXIT			ECC_GameTraceChannel4

UENUM(BlueprintType)
enum class EPPLevelState : uint8
{
	Intro,
	PingPong,
	GameOver
};

UENUM(BlueprintType)
enum class EPingPongState : uint8
{
	Intro,
	Serv,		// 공 생성, 서브
	Rally,
	RallyOver,	// 점수가 난 경우
	SetOver,	// 11점을 땄을 경우 1세트 종료. 5판 3승제
	//Deuce,		// 10:10 상황, 2점 차이가 날때까지 경기 계속
	MatchOver
};

UENUM(BlueprintType)
enum class EGameType : uint8
{
	PingPong
};

UENUM(BlueprintType)
enum class EEditMode : uint8
{
	Single,
	Multi
};

UENUM(BlueprintType)
enum class EPPBallState : uint8
{
	Serve,
	Recive
};

UENUM(BlueprintType)
enum class ETutoUIType : uint8
{
	AvatarGrab,
	UIClick,
	EXIT,
	Move
};


// 구조체
struct FPingPongData
{
public:

	int pointA;
	int pointB;
	int set;
	int scoreA;
	int scoreB;

	bool bServPlayer;	// 0 A, 1 B  -> 공 스폰 위치 결정 됨
	int servCount;	// 2번 서브 시 서브 변경
	bool bSpawnBall;	// 서브 시 공 한번만 생성되도록

	bool bIsDeuce;		// true시 듀스 상태. 점수 2점차 나야 세트 종료. 빠른 게임 모드시 비활성화 되어있음
};

