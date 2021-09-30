// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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