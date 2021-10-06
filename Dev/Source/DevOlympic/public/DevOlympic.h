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
	Serv,		// �� ����, ����
	Rally,
	RallyOver,	// ������ �� ���
	SetOver,	// 11���� ���� ��� 1��Ʈ ����. 5�� 3����
	//Deuce,		// 10:10 ��Ȳ, 2�� ���̰� �������� ��� ���
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


// ����ü
struct FPingPongData
{
public:

	int pointA;
	int pointB;
	int set;
	int scoreA;
	int scoreB;

	bool bServPlayer;	// 0 A, 1 B  -> �� ���� ��ġ ���� ��
	int servCount;	// 2�� ���� �� ���� ����
	bool bSpawnBall;	// ���� �� �� �ѹ��� �����ǵ���

	bool bIsDeuce;		// true�� �ེ ����. ���� 2���� ���� ��Ʈ ����. ���� ���� ���� ��Ȱ��ȭ �Ǿ�����
};

