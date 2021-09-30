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

	// # ����



	// # Ŭ���̾�Ʈ
	
	//	�ƹ�Ÿ ���� �� ���� ����
	int avatarID;	// 0 ������, 1 ������

	//	��Ƽ/ �̱� ���� ���� ����
	EEditMode modeNum = EEditMode::Single;

	//		# �̺�Ʈ �Լ�
	void SetAvatarNum(int id);	// �κ񿡼� �ƹ�Ÿ ���� �� ȣ���Ǵ� �Լ�
	void SetModeNum(EEditMode mode);	// �κ񿡼� ��� ���� �� ȣ��Ǵ� �Լ�

};
