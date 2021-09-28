#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_Point.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_Point : public AActor
{
	GENERATED_BODY()
	
public:	
	AWJ_Point();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Components)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Components)
	class UTextRenderComponent* pointA;

	UPROPERTY(EditAnywhere, Category = Components)
	class UTextRenderComponent* middle;

	UPROPERTY(EditAnywhere, Category = Components)
	class UTextRenderComponent* pointB;

	// # Order in World Outliner
	UPROPERTY(EditAnywhere, Category = Settings)
	int order;
	

	void SetPoint(int player, int point);
	void ResetPoint();

	void SetColor(FColor color);
};
