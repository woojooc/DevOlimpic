// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_SingleModeBall.generated.h"

UCLASS()
class DEVOLYMPIC_API ASJ_SingleModeBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_SingleModeBall();

	UPROPERTY(EditAnywhere, Category = SingleModeBall)
	class UStaticMeshComponent* ball;

	UPROPERTY(EditAnywhere, Category = SingleModeBall)
	class UStaticMeshComponent* wrapFX;

	// 충돌 사운드
	UPROPERTY(EditAnywhere, Category = PingPongSound)
		class USoundBase* pingpongSound;

	// 탁구공이 탁구대에 맞았을때 생기는 이펙트
	UPROPERTY(EditAnywhere, Category = HitPointEffect)
		class UParticleSystem* hitPointFX;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	class ASJ_SingleMode* singleModeBase;
};
