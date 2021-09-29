
#pragma once

#include "DevOlympic.h"
#include "Components/ActorComponent.h"
#include "WJ_ObjectPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVOLYMPIC_API UWJ_ObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWJ_ObjectPool();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	// # Ź��

	//		Ź���� ĳ��
	UPROPERTY(EditAnywhere, Category = PingPong_Settings)
	TSubclassOf<class ASJ_PingPongBall> pingpongFactory;

	//		Ź���� ��ȯ
	ASJ_PingPongBall* GetPingPongBall(AActor* actor, int player, EEditMode mode = EEditMode::Multi);
	const FVector offsetLocA = FVector{-120.f,0.f,150.f};
	const FVector offsetLocB = FVector{120.f,0.f,150.f};
};
