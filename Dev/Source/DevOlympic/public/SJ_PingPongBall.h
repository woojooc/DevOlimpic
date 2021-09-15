// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_PingPongBall.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_PingPongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_PingPongBall();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PingPongBall)
		class UStaticMeshComponent* meshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = PingPongBallSound)
	class USoundBase* pingpongSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// � �÷��̾ �ƴ��� �˻�, ���� ������ -1 ���� ������ ������ �ٽ� ���� �� ���� �ʱ�ȭ
	UPROPERTY(VisibleAnywhere, Category = PlayerID)
	int32 playerID = -1;

	// Side A �� �¾����� true
	UPROPERTY(VisibleAnywhere, Category = SideID)
	bool inSideA;

	// Side B �� �¾����� true
	UPROPERTY(VisibleAnywhere, Category = SideID)
	bool inSideB;

	// Bool �ʱ�ȭ �Լ�
	void InitSideState();
};
