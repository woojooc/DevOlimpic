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


	// # 서버 동기화
	FPingPongData fPPData;
	void SetFPPData(FPingPongData data);	// 서버에서 데이터 받아옴
	FPingPongData GetFPPData();

		// # 점수판	- 텍스트 오브젝트 캐싱
	TArray<class AWJ_Point*> pointPannelarr;

		// # 플레이어 캐싱
	class AActor* playerActorA;
	class AActor* playerActorB;


	// 핑퐁게임 프롤우 enum 변수 값 가져오기 또는 설정하기
	void SetState(EPingPongState state);
	EPingPongState GetState();

	// # 이벤트 함수
	void StartRally();		// 플레이어가 공을 치면 호출한다.

	// 0 PlayerA, 1 PlayerB가 친 공, in true 득점 false 실점
	void OnCollisionGround(int player, bool in);	/// point 득점 상황에서 호출된다.
	
	void NetServ();		// 서브시 공이 네트에 닿아 재 서브해야 되는 상황에서 호출된다.

	// # 싱글모드 
	// 서브 파워
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float sServePower = 2200;
	void autoServe();

	// 서브 상태 플로우
	EPPBallState p_State = EPPBallState::Serve;
	// 핑퐁 게임 플로우 enum
	EPingPongState m_state = EPingPongState::Intro;

private:
	UPROPERTY()
	class AVRGameModeBase* gameModeBase;

	// # 오토 서브 네트 포인트 캐싱
	int netZ = 92;
	class ASJ_PingPongBall* ppball;


	// # 플레이타임 조절 위한 점수 제한 변수
	int pointM = 5;		// 원래 룰은 11로 적용해야함.
	int scoreM = 3;		// 원래 룰은 5로 적용해야함. 그리고 scoreM-1 되어 있는 부분은 3이 되어야 함.

	// # 게임 점수, 스코어 저장 변수
	int pointA = 0;		// 11점 계산 ( 듀스시 11점 이상 가능 )
	int pointB = 0;

	int set = 1;		// 5세트 3승
	int scoreA = 0;		// 5세트 계산
	int scoreB = 0;

	// # 서브 관련 변수 저장
	bool bServPlayer = true;	// T/F 로 플레이어 A, B 서버 구분
	int servCount = 0;			// 2가 되면 서브 변경
	bool bSpawnBall = false;	// 서브시 공이 스폰되어 있으면 더이상 생성되지 않도록 확인

	bool bIsDeuce = false;		// (pointM-1) 10: 10 시 듀스.  2점차이가 날때까지 경기를 계속 한다.

	// # Flow 함수
	void Intro();
	void Serv();
	void Rally();
	void RallyOver();
	void SetOver();
	void MatchOver();

	void Setserve();
};
