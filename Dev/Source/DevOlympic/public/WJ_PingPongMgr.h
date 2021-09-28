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

private:

	UPROPERTY()
	class AVRGameModeBase* gameModeBase;

	// # EditModeSelect		- ��Ƽ || �̱� ����
	class AModeSelect* modeSelect;
	EEditMode editMode;		//ĳ���ؼ� ���

	// # ������	- �ؽ�Ʈ ������Ʈ ĳ��
	TArray<class AWJ_Point*> pointPannelarr;

	// # �÷��̾� ĳ��
	class AActor* playerActorA;
	class AActor* playerActorB;

	// # ���� ���� ��Ʈ ����Ʈ ĳ��
	int netZ = 92;
	class ASJ_PingPongBall* ppball;

	// ���� ���� �÷ο� enum
	EPingPongState m_state = EPingPongState::Intro;
	
	int pointA = 0;		// 11�� ��� ( �ེ�� 11�� �̻� ���� )
	int pointB = 0;

	int set = 1;		// 5��Ʈ 3��
	int scoreA = 0;		// 5��Ʈ ���
	int scoreB = 0;

	bool bServPlayer = true;	// T/F �� �÷��̾� A, B ���� ����
	int servCount = 0;			// 2�� �Ǹ� ���� ����
	bool bSpawnBall = false;	// ����� ���� �����Ǿ� ������ ���̻� �������� �ʵ��� Ȯ��

	bool bIsDeuce = false;		// 10: 10 �� �ེ.  2�����̰� �������� ��⸦ ��� �Ѵ�.

	void Intro();
	void Serv();
	void Rally();
	void RallyOver();
	void SetOver();
	void MatchOver();
};
