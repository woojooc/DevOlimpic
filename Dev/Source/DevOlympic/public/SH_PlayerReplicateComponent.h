// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SH_PlayerReplicateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API USH_PlayerReplicateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USH_PlayerReplicateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// 컴포넌트 소유한 플레이어의 위치 정보값 받아오기
	// 플레이어
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class APawn* player;

	// 플레이어 카메라
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UCameraComponent* playerCam;

	// 왼손 컨트롤러
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UMotionControllerComponent* leftController;

	// 오른손 컨트롤러
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UMotionControllerComponent* rightController;


	// 게임 시작함수
	void StartGame();


	// 동기화할 위치 값을 담을 트랜스폼 변수
	UPROPERTY()
		FTransform player_Tr;
	UPROPERTY()
		FTransform playerCam_Tr;
	UPROPERTY()
		FTransform leftController_Tr;
	UPROPERTY()
		FTransform rightController_Tr;


	// 위치 동기화 함수
	void  UpdateReplicate();

	// 클라이언트에서 서버로 함수를 호출하기 위한 선언
	// 자신의 컨트롤러 위치를 서버에게 전달
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdateReplicate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	bool Server_UpdateReplicate_Validate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	void Server_UpdateReplicate_Implementation(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);

	// 서버에서 클라이언트를 움직일 함수
	// 서버의 컨트롤러 위치를 클라이언트들에게 전달
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_UpdateReplicate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	bool Multi_UpdateReplicate_Validate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	void Multi_UpdateReplicate_Implementation(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
};
