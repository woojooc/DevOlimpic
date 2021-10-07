// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WJ_LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVOLYMPIC_API AWJ_LobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
public:
	AWJ_LobbyGameModeBase();

	virtual void BeginPlay() override;

	virtual void InitGameState() override;

	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "UIFunction")
	void HideMoveUI();
private:

	// Tuto
	UPROPERTY()
	TArray<class AWJ_TutorialObj*> avatarGrabUI;
	UPROPERTY()
	TArray<class AWJ_TutorialObj*> uiClickUI;
	UPROPERTY()
	TArray<class AWJ_TutorialObj*> moveUI;

	// Avatar List
	UPROPERTY()
	TArray<class AWJ_AvatarObj*> avatarObjs;
	
	// UI
	UPROPERTY(EditAnywhere, Category = "WorldObj")
	class AWJ_LobbyMenu* menuObj;

	UPROPERTY(EditAnywhere, Category = "WorldObj")
	class AActor* playPortObj;

	void OpenUI();
	void CloseUI();

	bool bOpenedUI = false;
};
