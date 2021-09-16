#pragma once

#include "DevOlympic.h"
#include "Components/ActorComponent.h"
#include "WJ_PingPongMgr.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API UWJ_PingPongMgr : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWJ_PingPongMgr();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetState(EPingPongState state);
	EPingPongState GetState();

	// # �̺�Ʈ �Լ�
	void StartRally();		// �÷��̾ ���� ġ�� ȣ���Ѵ�.
	void OnCollisionGround(int player, bool in);	/// ���� ���� ������ ȣ��ȴ�. 0 PlayerA, 1 PlayerB�� ģ ��, in true ���� false ����
	void NetServ();

private:

	UPROPERTY()
	class AVRGameModeBase* gameModeBase;

	// # EditModeSelect
	class AModeSelect* modeSelect;
	EEditMode editMode; //ĳ���ؼ� ���

	// # ������
	class AWJ_Point* pointPannel;
	class AWJ_Point* scorePannel;

	// # �÷��̾� ĳ��
	class AActor* playerActorA;
	class AActor* playerActorB;

	EPingPongState m_state = EPingPongState::Intro;
	int pointA = 0;	// 11��
	int pointB = 0;
	int set = 1;	// 5��Ʈ
	int scoreA = 0;
	int scoreB = 0;

	bool bServPlayer = true; // T/F �� �÷��̾� A, B ���� ����
	int servCount = 0;	// 2�� �Ǹ� ���� ����
	bool bSpawnBall = false;

	bool bIsDeuce = false;

	void Intro();
	void Serv();
	void Rally();
	void RallyOver();
	void SetOver();
	void MatchOver();
};
