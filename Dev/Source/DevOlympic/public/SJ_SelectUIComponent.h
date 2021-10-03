// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SJ_SelectUIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API USJ_SelectUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USJ_SelectUIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 손 조작 컨트롤을 위한 인풋 설정
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	// 왼손 애니메이션 인스턴스
	class UWJ_LobbyHandAnimInstance* l_handAnim;
	// 오른손 애니메이션 인스턴스
	class UWJ_LobbyHandAnimInstance* r_handAnim;
	class ASJ_PingPongPlayer* player;

	// 버튼 조작에 따라 바뀌는 왼손 애니메이션 변수
	float l_targetGripValue;
	// 버튼 조작에 따라 바뀌는 오른손 애니메이션 변수
	float r_targetGripValue;

	// 손 움직임 속도 조절 변수
	UPROPERTY(EditAnywhere, Category = "Hand Anim Setting")
	float gripSpeed = 20.0f;

	// 왼손 쥐기
	void GrabLeftHand();
	// 왼손 풀기
	void OpenLeftHand();
		
private:
	void ButtonClick();
	void ButtonRelease();
};
