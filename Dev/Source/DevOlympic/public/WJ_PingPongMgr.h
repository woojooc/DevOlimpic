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


	// # ���� ����ȭ
	FPingPongData fPPData;
	void SetFPPData(FPingPongData data);	// �������� ������ �޾ƿ�
	FPingPongData GetFPPData();

		// # ������	- �ؽ�Ʈ ������Ʈ ĳ��
	TArray<class AWJ_Point*> pointPannelarr;

		// # �÷��̾� ĳ��
	class AActor* playerActorA;
	class AActor* playerActorB;


	// �������� ���ѿ� enum ���� �� �������� �Ǵ� �����ϱ�
	void SetState(EPingPongState state);
	EPingPongState GetState();

	// # �̺�Ʈ �Լ�
	void StartRally();		// �÷��̾ ���� ġ�� ȣ���Ѵ�.

	// 0 PlayerA, 1 PlayerB�� ģ ��, in true ���� false ����
	void OnCollisionGround(int player, bool in);	/// point ���� ��Ȳ���� ȣ��ȴ�.
	
	void NetServ();		// ����� ���� ��Ʈ�� ��� �� �����ؾ� �Ǵ� ��Ȳ���� ȣ��ȴ�.

	// # �̱۸�� 
	// ���� �Ŀ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float sServePower = 2200;
	void autoServe();

	// ���� ���� �÷ο�
	EPPBallState p_State = EPPBallState::Serve;
	// ���� ���� �÷ο� enum
	EPingPongState m_state = EPingPongState::Intro;

private:
	UPROPERTY()
	class AVRGameModeBase* gameModeBase;

	// # ���� ���� ��Ʈ ����Ʈ ĳ��
	int netZ = 92;
	class ASJ_PingPongBall* ppball;


	// # �÷���Ÿ�� ���� ���� ���� ���� ����
	int pointM = 5;		// ���� ���� 11�� �����ؾ���.
	int scoreM = 3;		// ���� ���� 5�� �����ؾ���. �׸��� scoreM-1 �Ǿ� �ִ� �κ��� 3�� �Ǿ�� ��.

	// # ���� ����, ���ھ� ���� ����
	int pointA = 0;		// 11�� ��� ( �ེ�� 11�� �̻� ���� )
	int pointB = 0;

	int set = 1;		// 5��Ʈ 3��
	int scoreA = 0;		// 5��Ʈ ���
	int scoreB = 0;

	// # ���� ���� ���� ����
	bool bServPlayer = true;	// T/F �� �÷��̾� A, B ���� ����
	int servCount = 0;			// 2�� �Ǹ� ���� ����
	bool bSpawnBall = false;	// ����� ���� �����Ǿ� ������ ���̻� �������� �ʵ��� Ȯ��

	bool bIsDeuce = false;		// (pointM-1) 10: 10 �� �ེ.  2�����̰� �������� ��⸦ ��� �Ѵ�.

	// # Flow �Լ�
	void Intro();
	void Serv();
	void Rally();
	void RallyOver();
	void SetOver();
	void MatchOver();

	void Setserve();
};
