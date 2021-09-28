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

private:

	UPROPERTY()
	class AVRGameModeBase* gameModeBase;

	// # EditModeSelect		- 멀티 || 싱글 선택
	class AModeSelect* modeSelect;
	EEditMode editMode;		//캐싱해서 사용

	// # 점수판	- 텍스트 오브젝트 캐싱
	TArray<class AWJ_Point*> pointPannelarr;

	// # 플레이어 캐싱
	class AActor* playerActorA;
	class AActor* playerActorB;

	// # 오토 서브 네트 포인트 캐싱
	int netZ = 92;
	class ASJ_PingPongBall* ppball;

	// 핑퐁 게임 플로우 enum
	EPingPongState m_state = EPingPongState::Intro;
	
	int pointA = 0;		// 11점 계산 ( 듀스시 11점 이상 가능 )
	int pointB = 0;

	int set = 1;		// 5세트 3승
	int scoreA = 0;		// 5세트 계산
	int scoreB = 0;

	bool bServPlayer = true;	// T/F 로 플레이어 A, B 서버 구분
	int servCount = 0;			// 2가 되면 서브 변경
	bool bSpawnBall = false;	// 서브시 공이 스폰되어 있으면 더이상 생성되지 않도록 확인

	bool bIsDeuce = false;		// 10: 10 시 듀스.  2점차이가 날때까지 경기를 계속 한다.

	void Intro();
	void Serv();
	void Rally();
	void RallyOver();
	void SetOver();
	void MatchOver();
};
