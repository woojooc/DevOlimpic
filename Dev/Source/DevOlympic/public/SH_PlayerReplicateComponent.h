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


	// ������Ʈ ������ �÷��̾��� ��ġ ������ �޾ƿ���
	// �÷��̾�
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class APawn* player;

	// �÷��̾� ī�޶�
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UCameraComponent* playerCam;

	// �޼� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UMotionControllerComponent* leftController;

	// ������ ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, Category = "Replicate Setting")
	class UMotionControllerComponent* rightController;


	// ���� �����Լ�
	void StartGame();


	// ����ȭ�� ��ġ ���� ���� Ʈ������ ����
	UPROPERTY()
		FTransform player_Tr;
	UPROPERTY()
		FTransform playerCam_Tr;
	UPROPERTY()
		FTransform leftController_Tr;
	UPROPERTY()
		FTransform rightController_Tr;


	// ��ġ ����ȭ �Լ�
	void  UpdateReplicate();

	// Ŭ���̾�Ʈ���� ������ �Լ��� ȣ���ϱ� ���� ����
	// �ڽ��� ��Ʈ�ѷ� ��ġ�� �������� ����
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdateReplicate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	bool Server_UpdateReplicate_Validate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	void Server_UpdateReplicate_Implementation(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);

	// �������� Ŭ���̾�Ʈ�� ������ �Լ�
	// ������ ��Ʈ�ѷ� ��ġ�� Ŭ���̾�Ʈ�鿡�� ����
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_UpdateReplicate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	bool Multi_UpdateReplicate_Validate(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
	void Multi_UpdateReplicate_Implementation(FTransform playerTr, FTransform cameraTr, FTransform lcontTr, FTransform rcontTr);
};
