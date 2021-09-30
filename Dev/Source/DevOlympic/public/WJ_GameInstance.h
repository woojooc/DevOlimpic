// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DevOlympic.h"
#include "Engine/GameInstance.h"
#include "WJ_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API UWJ_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	// # 서버



	// # 클라이언트
	
	//	아바타 선택 시 정보 저장
	int avatarID;	// 0 마리오, 1 루이지

	//	멀티/ 싱글 선택 정보 저장
	EEditMode modeNum = EEditMode::Single;

	//		# 이벤트 함수
	void SetAvatarNum(int id);	// 로비에서 아바타 선택 시 호툴되는 함수
	void SetModeNum(EEditMode mode);	// 로비에서 모드 선택 시 호출되는 함수

};
