
#pragma once

#include "CoreMinimal.h"
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
	TSubclassOf<class APingPongBall> pingpoingFactory;

	//		Ź���� ��ȯ
	void GetPingPongBall(int player);

};
