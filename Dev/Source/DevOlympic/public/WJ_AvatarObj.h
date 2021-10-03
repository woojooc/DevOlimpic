
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_AvatarObj.generated.h"

UCLASS()
class DEVOLYMPIC_API AWJ_AvatarObj : public AActor
{
	GENERATED_BODY()
	
public:	
	AWJ_AvatarObj();

protected:
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Settings")
	int avatarID;

	UPROPERTY(EditAnywhere, Category = "Root")
	class UStaticMeshComponent* rootComp;
	UPROPERTY(EditAnywhere,Category = "Avatar")
	class UStaticMeshComponent* bodyComp;
	UPROPERTY(EditAnywhere, Category = "Avatar")
	class UStaticMeshComponent* headComp;

	UPROPERTY(EditAnywhere, Category = PickUpSettings)
	FVector grabOffset = FVector(0,0,-2);

	UPROPERTY(EditAnywhere, Category = PickUpSettings)
	FVector originalOffset = FVector(0,0,9);
};
