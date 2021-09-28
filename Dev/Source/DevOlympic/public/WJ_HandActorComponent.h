// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WJ_HandActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API UWJ_HandActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWJ_HandActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �� ���� ��Ʈ���� ���� ��ǲ ����
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);


	// �޼� �ִϸ��̼� �ν��Ͻ�
	class UWJ_LobbyHandAnimInstance* l_handAnim;
	// ������ �ִϸ��̼� �ν��Ͻ�
	class UWJ_LobbyHandAnimInstance* r_handAnim;
	class AWJ_LobbyPlayer* player;

	// ��ư ���ۿ� ���� �ٲ�� �޼� �ִϸ��̼� ����
	float l_targetGripValue;
	// ��ư ���ۿ� ���� �ٲ�� ������ �ִϸ��̼� ����
	float r_targetGripValue;

	// �� ������ �ӵ� ���� ����
	UPROPERTY(EditAnywhere, Category = "Hand Anim Setting")
		float gripSpeed = 20.0f;


	// �޼� ���
	void GrabLeftHand();
	// �޼� Ǯ��
	void OpenLeftHand();
	// ������ ���
	void GrabRIghtHand();
	// ������ Ǯ��
	void OpenRIghtHand();


	// Ŭ���� �ܼ� �浹�� �ƴ�
	// ����Ų ���� -> Ư�� ��ư�� �����ٸ� Ŭ������ �ν��Ͽ� �����ϰ� ��
private:
	void ButtonClick();
	void ButtonRelease();
};
